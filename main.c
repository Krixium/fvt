#include "main.h"
#include "forks.h"
#include "threads.h"
#include "primedecompose.h"

// include library header
#include "uwulib/uwuLib.h"

// include library implementation once
#define UWULIB_IMPL
#include "uwulib/uwuLib.h"

// global
pthread_mutex_t mutex;
FILE *factorsFile;
FILE *timerFile;

// constants
static const size_t numberOfWorkers = 8;
static const size_t numberOfInputs = 128000;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printUsage();
        return 0;
    }

    factorsFile = uwuOpenFile("output.txt", "w");

    if (!strcmp(argv[1], "fork"))
    {
        timerFile = uwuOpenFile("times-fork.txt", "a");
        runWithFork(&workerFunction, NULL, numberOfWorkers);
    }
    else if (!strcmp(argv[1], "thread"))
    {
        timerFile = uwuOpenFile("times-thread.txt", "a");
        runWithThreads(&workerFunction, NULL, numberOfWorkers);
    }
    else
    {
        printUsage();
    }

    uwuCloseFile(&factorsFile);
    uwuCloseFile(&timerFile);
    
    return 0;
}

void *workerFunction(void *args)
{
    // timer variables
    long d;
    struct timeval startTime;
    struct timeval endTime;
    struct timeval result;
    bzero(&startTime, sizeof(struct timeval));
    bzero(&endTime, sizeof(struct timeval));
    bzero(&result, sizeof(struct timeval));

    // decomposition varaibles
    unsigned long int inputs[numberOfInputs];
    mpz_t dest[1024];
    mpz_t n;
    int l;

    // start timer
    if (gettimeofday(&startTime, NULL))
    {
        perror("Getting start time failed.");
        return 0;
    }

    // populate input list
    for (int i = 0; i < numberOfInputs; i++)
    {
        inputs[i] = i + 1;
    }

    // decompose loop
    for (int i = 0; i < numberOfInputs; i++)
    {
        // decompose
        mpz_init_set_ui(n, inputs[i]);
        l = decompose(n, dest);

        // write results to ouptut file
        pthread_mutex_lock(&mutex);
        fprintf(factorsFile, "Results for %lu: ", inputs[i]);
        for (int j = 0; j < l; j++)
        {
            gmp_fprintf(factorsFile, "%s%Zd", j ? " * " : "", dest[j]);
            mpz_clear(dest[j]);
        }
        fprintf(factorsFile, "\n");
        pthread_mutex_unlock(&mutex);
    }

    // stop timer
    if (gettimeofday(&endTime, NULL))
    {
        perror("Getting end time failed.");
        return 0;
    }

    timersub(&endTime, &startTime, &result);
    d = result.tv_sec * 1000;
    d += result.tv_usec / 1000;
    fprintf(timerFile, "%lu\n", d);

    return NULL;
}

void printUsage()
{
    printf("%s\n", "./fvt [fork|thread]");
}
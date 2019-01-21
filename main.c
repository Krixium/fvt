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

// constants
static const size_t numberOfWorkers = 8;
static const size_t numberOfInputs = 16000;


int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printUsage();
        return 0;
    }

    if (!strcmp(argv[1], "fork"))
    {
        runWithFork(&workerFunction, NULL, numberOfWorkers);
    }
    else if (!strcmp(argv[1], "thread"))
    {
        runWithThreads(&workerFunction, NULL, numberOfWorkers);
    }
    else
    {
        printUsage();
    }
    
    return 0;
}

void *workerFunction(void *args)
{
    mpz_t dest[1024];

    unsigned long int inputs[numberOfInputs];

    mpz_t n;
    int l;

    for (int i = 0; i < numberOfInputs; i++)
    {
        inputs[i] = i + 1;
    }

    for (int i = 0; i < numberOfInputs; i++)
    {
        mpz_init_set_ui(n, inputs[i]);
        l = decompose(n, dest);

        pthread_mutex_lock(&mutex);
        printf("Results for %lu: ", inputs[i]);
        for (int j = 0; j < l; j++)
        {
            gmp_printf("%s%Zd", j ? " * " : "", dest[j]);
            mpz_clear(dest[j]);
        }
        printf("\n");
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void printUsage()
{
    printf("%s\n", "./fvt [fork|thread]");
}
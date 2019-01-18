#include <stdio.h>
#include <string.h>

#include "threads.h"
#include "res.h"

void *tempThreads(void *args)
{
    pthread_t id = *(pthread_t *)args;
    printf("The id of this thread is %d\n", (unsigned int)id);
    return NULL;
}

void runWithThreads()
{
    printf("%s\n", "running with threads ...");

    // Create array of workers
    pthread_t workers[WORKER_COUNT];
    bzero(workers, sizeof(workers));

    // Populate that array
    for (int i = 0; i < WORKER_COUNT; i++)
    {
        if (uwuCreateThread(workers + i, &tempThreads, (void *)workers + i))
        {
            perror("Creating of a worker thread failed!");
        }
    }

    for (int i = 0; i < WORKER_COUNT; i++)
    {
        if (uwuJoinThread(workers[i]))
        {
            perror("Faield to join worker thread!");
        }
    }
}
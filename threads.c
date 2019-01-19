#include <stdio.h>
#include <string.h>

#include "uwuLib/uwuLib.h"

#include "threads.h"

// replace this with actual work load
void *tempThreads(void *args)
{
    pthread_t id = *(pthread_t *)args;
    printf("The id of this thread is %d\n", (unsigned int)id);
    return NULL;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:            runWithThreads
--
-- DATE:                January 18, 2019
--
-- REVISIONS:           N/A
--
-- DESIGNER:            Benny Wang
--
-- PROGRAMMER:          Benny Wang
--
-- INTERFACE:           void runWithThreads(const size_t n)
--                          n: The number of desired workers.
--
-- NOTES:
--                      This function will spawn n workers using threads and will wait for all of them to complete.
----------------------------------------------------------------------------------------------------------------------*/
void runWithThreads(const size_t n)
{
    printf("%s\n", "running with threads ...");

    // Create array of workers
    pthread_t workers[n];
    bzero(workers, sizeof(workers));

    // Populate that array
    for (int i = 0; i < n; i++)
    {
        if (uwuCreateThread(workers + i, &tempThreads, (void *)workers + i))
        {
            perror("Creating of a worker thread failed!");
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (uwuJoinThread(workers[i]))
        {
            perror("Faield to join worker thread.");
        }
        printf("All workers have finished\n");
    }
}
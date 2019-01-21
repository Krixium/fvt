#include "uwulib/uwuLib.h"

#include "threads.h"

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
-- INTERFACE:           void runWithThreads(void *(*routine) (void *), void *args, const size_t n)
--                          routine: the worker routine.
--                          args: arguements for the routine.
--                          n: the number of desired workers.
--
-- NOTES:
--                      This function will spawn n workers threads and will wait for all of them to complete the given
--                      routine.
----------------------------------------------------------------------------------------------------------------------*/
void runWithThreads(void *(*routine) (void *), void *args, const size_t n)
{
    printf("%s\n", "running with threads ...");

    // Create array of workers
    pthread_t workers[n];
    bzero(workers, sizeof(workers));

    // Populate that array
    for (int i = 0; i < n; i++)
    {
        if (uwuCreateThread(workers + i, routine, args))
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
    }
    printf("All workers have finished\n");
}
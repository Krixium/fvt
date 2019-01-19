#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "forks.h"

// Replace this with actual workload
void *tempForks(void *args)
{
    printf("The id of this thread is %d\n", getpid());
    return NULL;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION:            runWithFork
--
-- DATE:                January 18, 2019
--
-- REVISIONS:           N/A
--
-- DESIGNER:            Benny Wang
--
-- PROGRAMMER:          Benny Wang
--
-- INTERFACE:           void runWithFork(const size_t n)
--                          n: The number of desired workers.
--
-- NOTES:
--                      This function will spawn n workers forks and will wait for all of them to complete.
----------------------------------------------------------------------------------------------------------------------*/
void runWithFork(const size_t n)
{
    printf("%s\n", "running with fork ...");

    // Create array of workers
    pid_t forkResult;
    pid_t workers[n];
    bzero(workers, sizeof(workers));

    // Populate that array
    for (int i = 0; i < n; i++)
    {
        forkResult = fork();
        workers[i] = forkResult;

        // If the process is the child
        if (forkResult == 0)
        {
            break;
        }
        // If the process is the parent
        else
        {
            continue;
        }
    }

    // If process is a child
    if (forkResult == 0)
    {
        tempForks(NULL);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if (waitpid(workers[i], NULL, 0) == -1)
            {
                perror("Faield to join worker thread.");
            }
        }

        printf("All workers have finished\n");
    }
}
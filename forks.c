#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "forks.h"
#include "res.h"

void *tempForks(void *args)
{
    printf("The id of this thread is %d\n", getpid());
    return NULL;
}

void runWithFork()
{
    printf("%s\n", "running with fork ...");

    // Create array of workers
    pid_t forkResult;
    pid_t workers[WORKER_COUNT];
    bzero(workers, sizeof(workers));

    // Populate that array
    for (int i = 0; i < WORKER_COUNT; i++)
    {
        forkResult = fork();
        workers[i] = forkResult;

        // If the worker is a parent
        if (forkResult == 0)
        {
            continue;
        }
        // If the worker is a child
        else
        {
            break;
        }
    }

    // If process is a child
    if (!fork())
    {
        tempForks(NULL);
    }
    else
    {
        for (int i = 0; i < WORKER_COUNT; i++)
        {
            waitpid(workers[i], NULL, 0);
        }
    }
}
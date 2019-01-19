#include <stdio.h>
#include <string.h>

#include "main.h"
#include "forks.h"
#include "threads.h"

static const size_t numberOfWorkers = 8;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printUsage();
        return 0;
    }

    if (!strcmp(argv[1], "fork"))
    {
        runWithFork(numberOfWorkers);
    }
    else if (!strcmp(argv[1], "thread"))
    {
        runWithThreads(numberOfWorkers);
    }
    else
    {
        printUsage();
    }
    
    return 0;
}

void printUsage()
{
    printf("%s\n", "./fvt [fork|thread]");
}
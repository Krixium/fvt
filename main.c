#include <stdio.h>
#include <string.h>

#include "main.h"
#include "forks.h"
#include "threads.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printUsage();
        return 0;
    }

    if (!strcmp(argv[1], "fork"))
    {
        runWithFork();
    }
    else if (!strcmp(argv[1], "thread"))
    {
        runWithThreads();
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
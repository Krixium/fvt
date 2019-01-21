#ifndef THREADS_H
#define THREADS_H

void runWithThreads(void *(*routine) (void *), void *args, const size_t n);

#endif
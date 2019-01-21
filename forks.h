#ifndef FORKS_H
#define FORKS_H

void runWithFork(void *(*routine) (void *), void *args, const size_t n);

#endif
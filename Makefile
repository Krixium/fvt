CC=gcc
CFLAGS=-Wall -ggdb
NAME=fvt.out
DEBUGNAME=fvtd.out

default: threads.o forks.o primedecompose.o main.o
	$(CC) $(CFLAGS) threads.o forks.o primedecompose.o main.o -o $(NAME) -lpthread -lgmp

debug: threads.o forks.o primedecompose.o main.o
	$(CC) $(CFLAGS) threads.o forks.o primedecompose.o main.o -ggdb -o $(DEBUGNAME) -lpthread -lgmp

main.o:
	$(CC) $(CFLAGS) -O -c main.c

threads.o:
	$(CC) $(CFLAGS) -O -c threads.c

forks.o:
	$(CC) $(CFLAGS) -O -c forks.c

primedecompose.o:
	$(CC) $(CFLAGS) -O -c primedecompose.c

clean:
	rm -f *.o *.txt *.bak $(NAME) $(DEBUGNAME)
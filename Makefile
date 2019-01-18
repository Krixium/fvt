CC=gcc
CFLAGS=-Wall -ggdb
NAME=fvt.out

default:  threads.o forks.o main.o
	$(CC) $(CFLAGS) main.o threads.o forks.o -o $(NAME) -lpthread

main.o:
	$(CC) $(CFLAGS) -O -c main.c

threads.o:
	$(CC) $(CFLAGS) -O -c threads.c

forks.o:
	$(CC) $(CFLAGS) -O -c forks.c

clean:
	rm -f *.o *.bak $(NAME)
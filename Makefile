CC=gcc
CFLAGS=-Wall -ggdb
'{ print $1 }'=fvt.out
DEBUGNAME=fvtd.out

default:  threads.o forks.o primedecompose.o main.o
	$(CC) $(CFLAGS) threads.o forks.o primedecompose.o main.o -o $('{ print $1 }') -lpthread -lgmp

debug:  threads.o forks.o primedecompose.o main.o
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
	rm -f *.o *.txt *.bak $('{ print $1 }') $(DEBUGNAME)
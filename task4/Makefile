CC=gcc

all: abonentBase

abonentBase: abonentBase.o
	$(CC) abonentBase.o -o abonentBase

abonentBase.o: abonentBase.c
	$(CC) -c abonentBase.c

clean:
	rm -f abonentBase *.o
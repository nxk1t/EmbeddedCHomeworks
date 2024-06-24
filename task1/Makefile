CC=gcc

all: bitOperations

bitOperations: bitOperations.o
	$(CC) bitOperations.o -o bitOperations

bitOperations.o: bitOperations.c
	$(CC) -c bitOperations.c

clean:
	rm -f bitOperations *.o

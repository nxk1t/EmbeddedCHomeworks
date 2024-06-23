CC=gcc

all: bitOperations

main: bitOperations.o
	$(CC) bitOperations.o -o bitOperations

main.o: bitOperations.c
	$(CC) -c bitOperations.c

clean:
	rm -f bitOperations *.o

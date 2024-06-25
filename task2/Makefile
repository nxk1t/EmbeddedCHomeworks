CC=gcc

all: arrays

arrays: arrays.o
	$(CC) arrays.o -o arrays

arrays.o: arrays.c
	$(CC) -c arrays.c

clean:
	rm -f arrays *.o
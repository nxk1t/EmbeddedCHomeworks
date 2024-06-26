CC=gcc

all: task3_1 task3_2 task3_3 task3_4

task3_1: task3_1.o
	$(CC) task3_1.o -o task3_1

task3_1.o: task3_1.c
	$(CC) -c task3_1.c

task3_2: task3_2.o
	$(CC) task3_2.o -o task3_2

task3_2.o: task3_2.c
	$(CC) -c task3_2.c

task3_3: task3_3.o
	$(CC) task3_3.o -o task3_3

task3_3.o: task3_3.c
	$(CC) -c task3_3.c

task3_4: task3_4.o
	$(CC) task3_4.o -o task3_4

task3_4.o: task3_4.c
	$(CC) -c task3_4.c

clean:
	rm -f task3_1 task3_2 task3_3 task3_4 *.o
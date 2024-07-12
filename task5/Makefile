CC := gcc

all: password getString

password: password.o
	$(CC) password.o -o password

password.o: password.c
	$(CC) -g -c -std=c89 -fno-stack-protector -no-pie password.c

getString: getString.o
	$(CC) getString.o -o getString

getString.o: getString.c
	$(CC) -c getString.c

clean:
	rm -f password getString *.txt *.o
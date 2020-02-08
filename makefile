CC=gcc

test: mstring.h mstring.c
	$(CC) mstring.h mstring.c mstring_test.c -o mstring_test;

main: mstring.h mstring.c
	$(CC) mstring.h mstring.c main.c -o main

clean:
	rm mstring_test main

CC=gcc
CFLAGS=-I.

closh: closh.o
			$(CC) -o closh closh.o

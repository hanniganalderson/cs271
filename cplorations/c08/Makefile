CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: main

main: main.o parser.o symtable.o error.o
	$(CC) $(CFLAGS) -o main main.o parser.o symtable.o error.o

main.o: main.c parser.h symtable.h error.h
parser.o: parser.c parser.h symtable.h error.h
symtable.o: symtable.c symtable.h
error.o: error.c error.h

clean:
	rm -f *.o main

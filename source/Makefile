CC = gcc
CFLAGS = -c -g
PROG = conway 
DEFAULT = generic

all: generic
	:
c_vecinos: vecinos.c
	$(CC) $(CFLAGS) vecinos.c

as_vecinos: vecinos.S
	$(CC) $(CFLAGS) vecinos.S

test: test.c
	$(CC) $(CFLAGS) test.c

mips: as_vecinos test
	$(CC) vecinos.o test.o -o $(PROG)

generic: c_vecinos test
	$(CC) vecinos.o test.o -o $(PROG)

	
clean:
	rm -rf *.o $(PROG)
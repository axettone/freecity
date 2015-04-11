CC=gcc
CFLAGS=-I.

all: freecity
%.o: %.c
	$(CC) -c -o $@ $<
freecity: main.o residentials.o economy.o school.o matrixsys.o ordinances.o menu.o map.o xmalloc.o
	gcc -o freecity main.o residentials.o economy.o school.c matrixsys.o ordinances.o menu.o map.o xmalloc.o -lm
clean:
	rm freecity *.o

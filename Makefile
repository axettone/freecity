CC=gcc
CFLAGS=-I. -w -g

all: freecity citymaker/citymaker

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

freecity: main.o residentials.o economy.o school.o matrixsys.o ordinances.o menu.o map.o xmalloc.o power.o storage.o city.o
	gcc -o freecity main.o residentials.o economy.o school.c matrixsys.o ordinances.o menu.o map.o xmalloc.o power.o storage.o city.o -lm

citymaker/citymaker:
	cd citymaker && $(MAKE)

clean:
	rm freecity *.o
	cd citymaker && $(MAKE) clean

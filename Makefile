CC=gcc
CFLAGS=-I. -I./models -w -g

all: freecity citymaker/citymaker models/modeldb

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

freecity: main.o utils.o economy.o residentials.o commercials.o industrials.o school.o matrixsys.o ordinances.o menu.o map.o xmalloc.o power.o storage.o city.o models/modeldbf.o
	gcc -o freecity main.o utils.o residentials.o commercials.o industrials.o economy.o school.c matrixsys.o ordinances.o menu.o map.o xmalloc.o power.o storage.o city.o models/modeldbf.o -lm

citymaker/citymaker:
	cd citymaker && $(MAKE)

models/modeldb:
	cd models && $(MAKE)

clean:
	rm freecity *.o
	cd citymaker && $(MAKE) clean
	cd models && $(MAKE) clean

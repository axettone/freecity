CC=gcc
CFLAGS=-I. -I../ -w -g

all: citymaker

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
citymaker: main.o ../utils.o ../economy.o credits.o parser.o fb.o ../map.o ../city.o ../residentials.o ../xmalloc.o
	gcc -o citymaker ../utils.o ../economy.o main.o credits.o parser.o fb.o ../map.o ../city.o ../residentials.o ../xmalloc.o
clean:
	rm citymaker *.o

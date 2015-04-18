CC=gcc
CFLAGS=-I. -I../ -w -g

all: citymaker

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
citymaker: main.o credits.o parser.o ../map.o ../city.o ../residentials.o ../xmalloc.o
	gcc -o citymaker main.o credits.o parser.o ../map.o ../city.o ../residentials.o ../xmalloc.o
clean:
	rm citymaker *.o

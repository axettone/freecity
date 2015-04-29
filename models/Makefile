CC=gcc
CFLAGS=-I. -I../ -w -g

all: modeldb

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

modeldb: main.o modeldbf.o ../economy.o ../xmalloc.o
	gcc -o modeldb main.o ../economy.o modeldbf.o ../xmalloc.o

clean:
	rm modeldb *.o

all: freecity
freecity: main.o residentials.o economy.o 
	gcc -o freecity main.o residentials.o economy.o
residentials.o: residentials.c
	gcc -c residentials.c
main.o: main.c
	gcc -c main.c
economy.o: economy.c
	gcc -c economy.c
clean:
	rm freecity *.o

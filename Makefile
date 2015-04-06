all: freecity
freecity: main.o residentials.o economy.o school.c 
	gcc -o freecity main.o residentials.o economy.o school.c
school.o: school.c
	gcc -c school.c
residentials.o: residentials.c
	gcc -c residentials.c
main.o: main.c
	gcc -c main.c
economy.o: economy.c
	gcc -c economy.c
clean:
	rm freecity *.o

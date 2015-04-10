all: freecity
freecity: main.o residentials.o economy.o school.o matrixsys.o ordinances.o menu.o map.o
	gcc -o freecity main.o residentials.o economy.o school.c matrixsys.o ordinances.o menu.o map.o -lm
map.o: map.c
	gcc -c map.c
menu.o: menu.c
	gcc -c menu.c
ordinances.o: ordinances.c
	gcc -c ordinances.c
matrixsys.o: matrixsys.c
	gcc -c matrixsys.c
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

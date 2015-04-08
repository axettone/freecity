all: freecity
freecity: main.o residentials.o economy.o school.o matrixsys.o ordinances.o
	gcc -o freecity main.o residentials.o economy.o school.c matrixsys.o ordinances.o -lm
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

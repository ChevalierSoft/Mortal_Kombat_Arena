START : main.o attaques.o init_structure.o affichage.o map.o
	gcc -o START main.o attaques.o init_structure.o affichage.o map.o
main.o : main.c fonctions.h personnage.h
	gcc -o main.o -c main.c
attaques.o : attaques.c fonctions.h personnage.h
	gcc -o attaques.o -c attaques.c
init_structure.o : init_structure.c fonctions.h personnage.h
	gcc -o init_structure.o -c init_structure.c
affichage.o : affichage.c fonctions.h personnage.h
	gcc -o affichage.o -c affichage.c -Wall -pedantic -ansi

map.o : map.c fonctions.h map.h
	gcc -o map.o -c map.c
clean:
	rm -rf *.o
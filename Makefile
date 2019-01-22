START : main.o attaques.o init_structure.o affichage.o
	gcc -o START main.o attaques.o init_structure.o affichage.o
main.o : main.c fonctions.h structure.h
	gcc -o main.o -c main.c
attaques.o : attaques.c fonctions.h structure.h
	gcc -o attaques.o -c attaques.c
init_structure.o : init_structure.c fonctions.h structure.h
	gcc -o init_structure.o -c init_structure.c
affichage.o : affichage.c fonctions.h structure.h
	gcc -o affichage.o -c affichage.c -Wall -pedantic -ansi
clean:
	rm -rf *.o

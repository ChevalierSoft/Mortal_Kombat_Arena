START : main.o attaques.o init_structure.o menu.o map.o liste_ptr.o
	gcc -o START main.o attaques.o init_structure.o menu.o map.o liste_ptr.o
main.o : main.c fonctions.h personnage.h menu.h
	gcc -o main.o -c main.c
attaques.o : attaques.c fonctions.h personnage.h menu.h
	gcc -o attaques.o -c attaques.c
init_structure.o : init_structure.c fonctions.h personnage.h menu.h liste_ptr.h
	gcc -o init_structure.o -c init_structure.c
menu.o : menu.c fonctions.h personnage.h menu.h
	gcc -o menu.o -c menu.c -Wall -pedantic -ansi
map.o : map.c fonctions.h map.h
	gcc -o map.o -c map.c
liste_ptr.o: liste_ptr.c liste_ptr.h
	gcc -o liste_ptr.o -c liste_ptr.c

clean:
	rm -rf *.o

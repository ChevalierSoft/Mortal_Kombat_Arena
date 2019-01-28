START : main.o attaques.o init_structure.o menu.o map.o
	gcc -o START main.o map.o
main.o : main.c fonctions.h personnage.h
	gcc -o main.o -c main.c




map.o : map.c fonctions.h map.h
	gcc -o map.o -c map.c
clean:
	rm -rf *.o

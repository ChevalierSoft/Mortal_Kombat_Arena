START : main.o attaques.o
	gcc -o START main.o attaques.o
main.o : main.c fonctions.h
	gcc -o main.o -c main.c
attaques.o : attaques.c fonctions.h
	gcc -o attaques.o -c attaques.c


clean:
	rm -rf *.o

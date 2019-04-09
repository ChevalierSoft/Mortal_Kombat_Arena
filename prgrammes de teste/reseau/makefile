
CC=gcc
FLAGS=-Wall -g -lcrypto

all: client serveur


%.o: %.c
	$(CC) -o $@ -c $< $(FLAGS)


client: client.o
	$(CC) -o $@ $^ $(LDFLAGS) -lcrypto

serveur: serveur.c
	$(CC) -o serveur serveur.c -lcrypto

clean:
	rm -rf *.o

mrproper: clean
	rm -rf $(EXEC)



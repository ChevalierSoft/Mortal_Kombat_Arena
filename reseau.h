#ifndef H_R
#define H_R

#include "fonctions.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <openssl/md5.h>

typedef struct{
	int id, choix_menu, numero_fonction, tx, ty;
} action_t;

void menu_online();

#endif

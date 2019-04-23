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

void menu_online(carte_t * pt_m);
void aff_action(action_t * a);

#endif

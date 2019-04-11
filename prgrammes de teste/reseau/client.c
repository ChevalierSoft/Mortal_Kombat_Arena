#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <openssl/md5.h>

#define H_COLOR
#define BLK   "\x1B[30m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//#define SERVEURNAME "192.168.1.106" // adresse IP de mon serveur
#define SERVEURNAME "127.0.1.1" // adresse IP de mon serveur
#define client_id "Ash"
#define QUITTER "QUITTER"

typedef struct{
	int id, choix_menu, numero_fonction, tx, ty;
} action_t;

void quitter(int to_server_socket){
	printf("[client] envoi message QUITTER au serveur\n");
	send(to_server_socket,QUITTER,7,0);
}

char *str2md5(const char * str, int length) {
    int n;
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }

    MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

char * f2s(const char * file_name) {
    
    char * file_contents;    // fichier chargé
    long input_file_size=1000; //c'est zéro mais bon...
    FILE * input_file = fopen(file_name, "rb");
    //printf("->%s\n", file_name);
    fseek(input_file, 0, SEEK_END);
    input_file_size = ftell(input_file);
    rewind(input_file);
    file_contents = malloc(input_file_size * (sizeof(char)));
    fread(file_contents, sizeof(char), input_file_size, input_file);
    //printf("%s\n",file_contents );
    fclose(input_file);
    return(file_contents);
}

char * get_md5(char * file_name){

  char * file_contents = f2s(file_name);

  char * output = str2md5(file_contents, strlen(file_contents));
  //printf("%s\n", output);
  //free(output);
  free(file_contents);
  
  return(output);
}

static int nb_digit(char* s){
	int nb=0;

	while(*s){
		nb++;
		s++;
	}

	return(nb);
}

static int c2i(char i){

	return(i-'0');
}

static int a2i(char* s){
	
	int i=0;
	int neg=1;
 	int res=0;
	int nb=nb_digit(s);

 	if ( *s == '-' ){
 		neg=-1;
 		i++;
 		(*s)++;
 	}
 	for(; i<nb ; i++){
 		res*=10;
 		res += c2i(s[i]);
 	}
 	return(neg*res);
}

int recive_int(int to_server_socket){
	char buffer[512];
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	return(a2i(buffer));
}

void send_msg(int to_server_socket, char * msg){
	char buffer[512];
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, msg);
	//printf("buffer : %s\n", buffer);
	send(to_server_socket, buffer, strlen(buffer),0);

}

void recive_action(int to_server_socket, action_t *action_serv){
	
	printf(YEL"####reception####\n"RESET);

	action_serv->id = recive_int(to_server_socket);
  send_msg(to_server_socket, "ok");
  action_serv->choix_menu = recive_int(to_server_socket);
  send_msg(to_server_socket, "ok");
  action_serv->numero_fonction = recive_int(to_server_socket);
  send_msg(to_server_socket, "ok");
	action_serv->tx = recive_int(to_server_socket);
	send_msg(to_server_socket, "ok");
	action_serv->ty = recive_int(to_server_socket);
	send_msg(to_server_socket, "ok");

	printf(YEL"###traitement###\n"RESET);
  printf("id = %d\n", action_serv->id);
	
  if(action_serv->choix_menu==1){
  	printf("choix = attaque\n");
  	if (action_serv->numero_fonction > 0){
  		printf("numero de la fonction d'attaque = %d\n", action_serv->numero_fonction);
  		printf("nom du spell en : tx = %d ty = %d\n", action_serv->tx, action_serv->ty);
  	}
  	//faudra comparer avec nb_spell du perso's id
  	//execute le spell[numero_fonction-1] du perso 
  }
  else if (action_serv->choix_menu==2){
  	printf("choix = deplacement\n");
  	printf("deplacement en : tx = %d ty = %d\n", action_serv->tx, action_serv->ty);
  }
  else if (action_serv->choix_menu==3){
  	printf("choix = passe son tour\n");
  	//ne rien faire
  }
  else if (action_serv->choix_menu==5){
  	printf("choix = abandon\n");
  	//gg(team2);
  }

  
	printf(YEL"################\n"RESET);
  
}



//####################################################################


int main (  int argc, char** argv ){

	system("clear");
	struct sockaddr_in serveur_addr;
	struct hostent *serveur_info;
	long hostAddr;
	char buffer[512];
	int to_server_socket;
	int port = 30410;

	bzero(&serveur_addr,sizeof(serveur_addr));
	hostAddr = inet_addr(SERVEURNAME);
	if ( (long)hostAddr != (long)-1 ){
		bcopy(&hostAddr,&serveur_addr.sin_addr,sizeof(hostAddr));
	}
	else {
		serveur_info = gethostbyname(SERVEURNAME);
	  	if (serveur_info == NULL) {
			printf("Impossible de récupérer les infos du serveur\n");
			exit(0);
	  	}
	  	bcopy(serveur_info->h_addr,&serveur_addr.sin_addr,serveur_info->h_length);
	}
	serveur_addr.sin_port = htons(port);
	serveur_addr.sin_family = AF_INET;
	/* creation de la socket */
	if ( (to_server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		printf("Impossible de créer la socket client\n");
	  	exit(0);
	}
	/* requete de connexion */
	if(connect( to_server_socket, (struct sockaddr *)&serveur_addr, sizeof(serveur_addr)) < 0 ) {
		printf("Impossible de se connecter au serveur\n");
	  	exit(0);
	}
	/* envoie de données et reception */


/*---------------------------------------------------------------------------------------*/
	//printf("port : %d\n",port);

	//connection !
	send_msg(to_server_socket, "Connection client");

	//nom du serveur?
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	printf(YEL"[serveur] %s \n"RESET, buffer);
	char server_id[512];
	strcpy(server_id, buffer);

	//nom client !
	send_msg(to_server_socket, client_id);

	//Ready ?
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	printf(YEL"[%s] %s \n"RESET, server_id, buffer);

	//Ready !
	memset(buffer, 0, sizeof(buffer));
	printf("Pret ? (o|y)\n");
  //getchar();														<------
  send_msg(to_server_socket, "Client pret");

  //nom fichier save à md5 ?
  memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	printf(YEL"[%s] %s \n"RESET, server_id, buffer);
	char nomFichier[512];// = "p_save.txt";
  strncpy(nomFichier, buffer, 512);
  //printf("fichier a charger : %s\n", nomFichier);

	//md5 !
	char * client_md5 = get_md5(nomFichier);
	printf("client_md5 : %s\n", client_md5);
	send_msg(to_server_socket, client_md5);
	free(client_md5); //hé oui, faut free
  
  //Start
  printf(RED"La partie commence\n"RESET);

  //enregistrement d'une action
  action_t * action_serv = malloc(sizeof(action_serv));
	recive_action(to_server_socket, action_serv);







	/* fermeture de la connexion */
	shutdown(to_server_socket,2);
	close(to_server_socket);
	return 0;
}


/*pensser à une sortie si on initialise un perso 
en dehors de la map par faute de taille*/
/*verifier les fichiers ouverts*/
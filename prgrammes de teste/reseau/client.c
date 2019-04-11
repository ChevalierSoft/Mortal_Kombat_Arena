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

char menu(){
	char choix;
	printf("Que voulez-vous faire ?\n");
	printf("m: envoyer un message au serveur\n");
	printf("q: quitter\n");
	printf("Que voulez-vous faire ?\n");
	scanf(" %c", &choix);
	return choix;
}

void envoyer_message(int to_server_socket){
	char msg[200], buffer[512];
	printf("quel est votre message : ");
	scanf(" %[^\n]s", buffer);
	sprintf(msg, "MSG %s", buffer);
	send(to_server_socket, msg, strlen(msg), 0); //on augmente la taille de 4 pour l'entête
	// lecture de la réponse
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket,buffer,512,0);
	printf(MAG"[client] reponse du serveur : '%s'\n"RESET, buffer);
	/*if(strncmp("MSG", buffer, 3)==0){
			printf("[serveur] message reçu : '%s'\n",buffer+4);
			//printf("[serveur] envoi de la réponse ");
			//sprintf(buffer,"REPONSE DU SERVEUR");
			envoyer_message(client_socket);
			//send(client_socket, buffer, 512, 0);
	}*/
}

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
 	printf("%d\n", neg*res);
 	return(neg*res);

}

void recive_int(int to_server_socket, int *id){

	char buffer[512];
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	*id = a2i(buffer);
}

void send_msg(int to_server_socket, char * msg){
	char buffer[512];
	memset(buffer, 0, sizeof(buffer));
	strcpy(buffer, msg);
	send(to_server_socket, client_id, strlen(client_id),0);

}


//####################################################################


int main (  int argc, char** argv ){

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
	sprintf(buffer, "Connection client");
	send(to_server_socket, buffer, strlen(buffer),0);

	//nom du serveur?
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	printf(YEL"[serveur] %s \n"RESET, buffer);
	char server_id[512];
	strcpy(server_id, buffer);

	//nom client !
	memset(buffer, 0, sizeof(buffer));
	send(to_server_socket, client_id, strlen(client_id),0);

	//Ready ?
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	printf(YEL"[%s] %s \n"RESET, server_id, buffer);

	//Ready !
	memset(buffer, 0, sizeof(buffer));
	printf("Pret ? (o|y)\n");
  getchar();
  sprintf(buffer,"Client pret");
  send(to_server_socket, buffer, strlen(buffer),0);

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

	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, client_md5);
	send(to_server_socket, buffer, strlen(buffer),0);
	free(client_md5); //hé oui, faut free
  
  //Start
  printf(RED"La partie commence\n"RESET);

  //enregistrement d'une action
  int id=0;
  recive_int(to_server_socket, &id);
  printf("id = %d\n", id);

  send_msg(to_server_socket, "ok");

	int choix_menu = 0;
	recive_int(to_server_socket, &choix_menu);
  if(choix_menu==1)
  	printf("choix = attaque\n");
  else if (choix_menu==2)
  	printf("choix = deplacement\n");
  else if (choix_menu==3)
  	printf("choix = abandon\n");
  else if (choix_menu==4)
  	printf("choix = passe son tour\n");


/*
	int numero_fonction = 0;
	recive_int(to_server_socket, &numero_fonction);
  printf("numero_fonction = %d\n", numero_fonction);

	int tx = 0;
	recive_int(to_server_socket, &tx);
  printf("tx = %d\n", tx);

	int ty = 0;
	recive_int(to_server_socket, &ty);
  printf("ty = %d\n", ty);
*/



	/* fermeture de la connexion */
	shutdown(to_server_socket,2);
	close(to_server_socket);
	return 0;
}

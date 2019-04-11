#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <unistd.h>
#include <openssl/md5.h>

#define BLK   "\x1B[30m"
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

//char * serveur_id = "DaBoi";
#define serveur_id "DaBoi"

char buffer[512];

void fin(int sig){
	printf("fin du serveur");
}

int hostname_to_ip(char * hostname , char* ip){

    struct hostent *he;
    struct in_addr **addr_list;
    int i;

    if ( (he = gethostbyname( hostname ) ) == NULL)
    {
        // get the host info
        herror("gethostbyname");
        return 1;
    }

    addr_list = (struct in_addr **) he->h_addr_list;

    for(i = 0; addr_list[i] != NULL; i++)
    {
        //Return the first one;
        strcpy(ip , inet_ntoa(*addr_list[i]) );
        return 0;
    }

    return 1;
}

void view_ip(){
  char s[256];
  struct hostent *host;
  struct in_addr **adr;
  if (!gethostname(s, 256))
    if ((host = gethostbyname(s)) != NULL)
      for (adr = (struct in_addr **)host->h_addr_list; *adr; adr++)
          printf("IP : %s\n", inet_ntoa(**adr));
}

void envoyer_message(int client_socket){
	char msg[200], buffer[512];
	printf("quel est votre message de reponse : ");
	scanf(" %[^\n]s", buffer);
	sprintf(msg, "MSG %s", buffer);
	send(client_socket, msg, strlen(msg), 0); //on augmente la taille de 4 pour l'entête
	// lecture de la réponse
	memset(buffer, 0, sizeof(buffer));
	recv(client_socket,buffer,512,0);
	printf("[client] reponse du serveur : '%s'\n", buffer);
}
/*
void quick_send(int client_socket){
	char msg[200], buffer[512];
	printf("quel est votre message de reponse : ");
	scanf(" %[^\n]s", buffer);
	sprintf(msg, "MSG %s", buffer);
	send(client_socket, msg, strlen(msg), 0); //on augmente la taille de 4 pour l'entête
	// lecture de la réponse
	memset(buffer, 0, sizeof(buffer));
	recv(client_socket,buffer,512,0);
	printf("[client] reponse du serveur : '%s'\n", buffer);
}
*/
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

static char i2c(int i){

	return(i+'0');
}

char *i2a(int i/*,char *s*/){
	char *s;
	s=malloc(sizeof(char)*6);
	int neg=0;
 	 int tmp=0;
	  int j=0;

 	if (i < 0){
 		neg=1;
 		i*=-1;
 	}
 	
 	while(i!=0 && j<6){
		tmp=i%10;
		i/=10;
		s[j]=i2c(tmp);
		j++;
	}
	if (neg==1)
		s[j++]='-';
	s[j]='\0';

	return(s);
}

void send_int(int client_socket, int vald){

	char buffer[512];
	char * better_vald = i2a(vald);
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, better_vald);
	send(client_socket, buffer, strlen(buffer), 0);
	free(better_vald);

}
int recive_ok(int client_socket){
	char buffer[512];
	memset(buffer, 0, sizeof(buffer));
  recv(client_socket, buffer, 512,0);
  if (strcmp(buffer, "ok"))
  	return(1);
  return(0);
}


//####################################################################


int main ( void ){

	int ma_socket;
	int client_socket;
	struct sockaddr_in mon_address, client_address;
	unsigned int mon_address_longueur, lg;
	bzero(&mon_address,sizeof(mon_address));
	mon_address.sin_port = htons(30410);
	mon_address.sin_family = AF_INET;
	mon_address.sin_addr.s_addr = htonl(INADDR_ANY);

	char *hostname = "localhost";
  char ip[100];

  hostname_to_ip(hostname , ip);
	fprintf(stderr, "%s resolved to %s" , hostname , ip);
	view_ip();

	/* creation de socket */
	if ((ma_socket = socket(AF_INET,SOCK_STREAM,0))== -1) {
		printf("Impossible de créer la socket\n");
		exit(0);
	}

	/* bind serveur - socket */
	bind(ma_socket,(struct sockaddr *)&mon_address,sizeof(mon_address));
	/* ecoute sur la socket */
	listen(ma_socket,5);
	/* accept la connexion */
	mon_address_longueur = sizeof(client_address);

    /* on attend que le client se connecte */
	client_socket = accept(ma_socket,
                         (struct sockaddr *)&client_address,
                         &mon_address_longueur);

	//int quitter=0;
  //while(!quitter){

	/************************************************************/

	//connection !
	memset(buffer, 0, sizeof(buffer));
	recv(client_socket, buffer, 512,0);

	//envoie du nom serveur
  printf(YEL"[client] %s \n"RESET, buffer);
  memset(buffer, 0, sizeof(buffer));
	printf("envoie du serveur_id %s\n", serveur_id);
	sprintf(buffer,"DaBoi");
	send(client_socket, buffer, strlen(buffer), 0);

	//reception du nom du client
  memset(buffer, 0, sizeof(buffer));
  recv(client_socket, buffer, 512,0);
  char client_id[512];
	strcpy(client_id, buffer);
  printf("client_id : %s \n" , client_id);

  //Ready?
  printf("Pret ? (o|y)\n");
  getchar();
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer,"Ready ?");
  send(client_socket, buffer, strlen(buffer), 0);

  //Ready !
  memset(buffer, 0, sizeof(buffer));
  recv(client_socket, buffer, 512,0);
  printf(YEL"[%s] %s \n"RESET, client_id, buffer);
  
  //nom fichier save à md5 ?
  char * nomFichier = "p_save.txt";
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, nomFichier);
  send(client_socket, buffer, strlen(buffer), 0);


  //md5 !
  memset(buffer, 0, sizeof(buffer));
  recv(client_socket, buffer, 512,0);
  printf(YEL"[%s] %s \n"RESET, client_id, buffer);
  printf(YEL"tst	\n"RESET);

  char * serveur_md5 = get_md5(nomFichier);

	printf("hash du fichier %s : %s\n", nomFichier, serveur_md5);
  
  if(! strcmp(buffer,serveur_md5))
  	printf(CYN"Sauvegarde valide\n"RESET);
  else
  	printf(RED"Sauvegarde Erronee\n"RESET);

	free(serveur_md5); //hé oui, faut free

		  
	//Start
	printf(RED"La partie commence\n"RESET);

	//va falloir enregistrer les retours avec des modulo
	//l'Host va tj commancer pour l'instant

	//envoie d'une action
	int id = 1;
	send_int(client_socket, id);

	recive_ok(client_socket);

	int choix_menu = 1;
	send_int(client_socket, choix_menu);

	/*int numero_fonction = 3;
	send_int(client_socket, numero_fonction);

	int tx = 2;
	send_int(client_socket, tx);

	int ty = 1;
	send_int(client_socket, ty);
	*/


	shutdown(ma_socket,2);
	close(ma_socket);
	return 0;
}



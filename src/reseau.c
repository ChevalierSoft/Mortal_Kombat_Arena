#include "reseau.h"

//#define SERVEURNAME "127.0.1.1" // adresse IP de mon serveur
#define QUITTER "QUITTER"


void fin(void){

	printf("fin du serveur");
}

void quitter(int to_server_socket){
	printf("[client] envoi message QUITTER au serveur\n");
	send(to_server_socket,QUITTER,7,0);
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

static int c2i(char i){

	return(i-'0');
}

char *i2a(int i){
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

static int nb_digit(char* s){
	int nb=0;

	while(*s){
		nb++;
		s++;
	}

	return(nb);
}

int a2i(char* s){
	
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

void send_msg(int to_server_socket, char * msg){
	char buffer[512];
	memset(buffer, 0, sizeof(buffer));
	sprintf(buffer, msg);
	//printf("buffer : %s\n", buffer);
	send(to_server_socket, buffer, strlen(buffer),0);
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

int recive_int(int to_server_socket){
	char buffer[512];
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	return(a2i(buffer));
}
void aff_action(action_t * a){
	printf("action : %d %d %d %d %d\n",a->id, a->choix_menu, a->numero_fonction, a->tx, a->ty);
}
void send_action(int client_socket, action_t * a){

	aff_action(a);
	
	send_int(client_socket,a->id);
	recive_ok(client_socket);

	send_int(client_socket,a->choix_menu);
	recive_ok(client_socket);

	send_int(client_socket,a->numero_fonction);
	recive_ok(client_socket);
	
	send_int(client_socket,a->tx);
	recive_ok(client_socket);

	send_int(client_socket,a->ty);
	recive_ok(client_socket);
}

void recive_action(int to_server_socket, action_t *a, carte_t * pt_m){
	
	printf(YEL"####reception####\n"RESET);

	a->id = recive_int(to_server_socket);
  send_msg(to_server_socket, "ok");
  a->choix_menu = recive_int(to_server_socket);
  send_msg(to_server_socket, "ok");
  a->numero_fonction = recive_int(to_server_socket);
  send_msg(to_server_socket, "ok");
	a->tx = recive_int(to_server_socket);
	send_msg(to_server_socket, "ok");
	a->ty = recive_int(to_server_socket);
	send_msg(to_server_socket, "ok");

	printf(YEL"###traitement###\n"RESET);
  printf("id = %d\n", a->id);
	
  if(a->choix_menu==1){
  	printf("choix = attaque\n");
  	if (a->numero_fonction > 0){
  		printf("numero de la fonction d'attaque = %d\n", a->numero_fonction-1);
  		printf("nom du spell en : tx = %d ty = %d\n", a->tx, a->ty);
  		
  		personnage_t * perso;
			valeur_elt(&perso);	//ce serait bien de lechercher par son id avant
			info_personnage(perso);
			
			perso->tab_spell[a->numero_fonction-1](perso,pt_m,a->tx,a->ty);
  	}
  	//faudra comparer avec nb_spell du perso's id
  	//execute le spell[numero_fonction-1] du perso 
  }
  else if (a->choix_menu==2){
  	printf("choix = deplacement\n");
  	printf("deplacement en : tx = %d ty = %d\n", a->tx, a->ty);
  }
  else if (a->choix_menu==3){
  	printf("choix = passe son tour\n");
  	//ne rien faire
  }
  else if (a->choix_menu==5){
  	printf("choix = abandon\n");
  	//gg(team2);
  }

  
	printf(YEL"################\n"RESET);
}



//####################################################################


int hosting_game(carte_t * pt_m){

	//csystem("clear");
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
  char buffer[512];
  char * serveur_id = "DaBoi";

  printf(MAG"En attente d'un client port 30410\n");

  hostname_to_ip(hostname , ip);
	printf("%s resolved to %s\n" CYN, hostname , ip);
	view_ip();
	printf(""RESET );
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
  getchar();//														<------
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer,"Ready ?");
  send(client_socket, buffer, strlen(buffer), 0);

  //Ready !
  memset(buffer, 0, sizeof(buffer));
  recv(client_socket, buffer, 512,0);
  printf(YEL"[%s] %s \n"RESET, client_id, buffer);
  
  //nom fichier save à md5 ?
  char * nomFichier = "save/p_save.txt";	//à changer
  memset(buffer, 0, sizeof(buffer));
  sprintf(buffer, nomFichier);
  send(client_socket, buffer, strlen(buffer), 0);


  //md5 !
  memset(buffer, 0, sizeof(buffer));
  recv(client_socket, buffer, 512,0);
  printf(YEL"[%s] %s \n"RESET, client_id, buffer);
  printf(YEL"_	\n"RESET);

  char * serveur_md5 = get_md5(nomFichier);

	printf("hash du fichier %s : %s\n", nomFichier, serveur_md5);
  
  if(! strcmp(buffer,serveur_md5))
  	printf(CYN"Sauvegarde valide\n"RESET);
  else
  	printf(RED"Sauvegarde Erronee\n"RESET);

	free(serveur_md5); //hé oui, faut free

		  
	//Start
	printf(RED"La partie commence\n"RESET);
	printf("Envoie d'une action --->\n");
	//va falloir enregistrer les retours avec des modulo
	//l'Host va tj commancer pour l'instant
	

	
	//envoie d'une action
	action_t * action_serv=NULL; // = malloc(sizeof(action_serv));
	action_t * action_client=NULL; // = malloc(sizeof(action_client));

	//position_t * pos_tmp=NULL;// = malloc(sizeof(pos_tmp));

	int web = 1;
	//position_t pos_tmp;
	/*
	//sera defini a la fin de getXY
	action_serv->id = 1;
	action_serv->choix_menu = 1;
	action_serv->numero_fonction = 3;
	action_serv->tx = 2;
	action_serv->ty = 1;

	send_action(client_socket, action_serv);
	*/
	int ma_team = 1;
	if (!liste_vide()){
    /*bouleen de lancement de partie*/
    int partie_en_cours = 1;
    int team = 1;
    /*barre de vie de la team*/
    int hp_team1=1, hp_team2=1;
    /*tmp prendra la valeur des personnages de la liste succecivement*/
    personnage_t * tmp;

    while(partie_en_cours){
    	/*affiche la liste des perso à chaque tours*/
  		afficher_liste();
    	en_tete();
      team = 1;
  		/*boucle pour un tour*/
      while(!hors_liste()){

        detection_etat(pt_m);
        hp_team1=get_hp_team(1);
        hp_team2=get_hp_team(2);
        /*condition d'arret de la partie*/
        if (hp_team1<=0 || hp_team2<=0){
          partie_en_cours=0;
          break;
        }
        valeur_elt(&tmp);
        if(!strcmp(tmp->pp, "👽")){    /*  /!\   probleme ici pour les poisons et autre qui font le double des degats du au delimiteur */
          team = 2;
        } 
        else if(tmp->pv>0 && team == ma_team) {

          afficher_map(pt_m);
    		  info_personnage(tmp);
          /*printf("infos affiches\n");*/
    		  action_serv = menu_choix(tmp, pt_m, web);
    		  if(web)
    		  	send_action(client_socket, action_serv);
    		  
        }
        else if (tmp->pv>0 && team != ma_team){
        	afficher_map(pt_m);
    		  info_personnage(tmp);
        	//enregistrement d'une action
  				action_t * action_client = malloc(sizeof(action_client));
					recive_action(client_socket, action_client, pt_m);
					free(action_client);
				}
        suivant();
      }

    }
	  detection_etat(pt_m);
	  afficher_map(pt_m);

	  if (hp_team1>hp_team2)
	    gg(serveur_id);    
	  else
	    gg(client_id);

	  free(action_serv);
	  free(action_client);

  }
  

	shutdown(ma_socket,2);
	close(ma_socket);
	return 0;
}


int joining_game(carte_t * pt_m){

	//system("clear");
	struct sockaddr_in serveur_addr;
	struct hostent *serveur_info;
	long hostAddr;
	char buffer[512];
	int to_server_socket;
	int port = 30410;
	char * client_id = "Ash";

	printf(MAG"Rejoindre une partie\n"RESET);
	printf("donnre l'addresse ip :\n");
	char SERVEURNAME[16];
	scanf("%s", SERVEURNAME );
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
	char serveur_id[512];
	strcpy(serveur_id, buffer);

	//nom client !
	send_msg(to_server_socket, client_id);

	//Ready ?
	memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	printf(YEL"[%s] %s \n"RESET, serveur_id, buffer);

	//Ready !
	memset(buffer, 0, sizeof(buffer));
	printf("Pret ? (o|y)\n");
  getchar();//														<------
  send_msg(to_server_socket, "Client pret");

  //nom fichier save à md5 ?
  memset(buffer, 0, sizeof(buffer));
	recv(to_server_socket, buffer, 512, 0);
	printf(YEL"[%s] %s \n"RESET, serveur_id, buffer);
	char nomFichier[512];// = "p_save.txt";
  strncpy(nomFichier, buffer, 512);

  //concatene(, nomFichier)

  //printf("fichier a charger : %s\n", nomFichier);

	//md5 !
	char * client_md5 = get_md5(nomFichier);	// //"save/lvl1.p"
	printf("client_md5 : %s\n", client_md5);
	send_msg(to_server_socket, client_md5);
	free(client_md5); //hé oui, faut free
  
  //Start
  printf(RED"La partie commence\n"RESET);

  en_tete();


	//initialisation des actions
	action_t * action_serv=NULL; // = malloc(sizeof(action_serv));
	action_t * action_client=NULL; // = malloc(sizeof(action_client));

	int web = 1;
	int ma_team = 2;

	if (!liste_vide()){
    /*bouleen de lancement de partie*/
    int partie_en_cours = 1;
    int team = 1;
    /*barre de vie de la team*/
    int hp_team1=1, hp_team2=1;
    /*tmp prendra la valeur des personnages de la liste succecivement*/
    personnage_t * tmp;

    while(partie_en_cours){
    	/*affiche la liste des perso à chaque tours*/
  		afficher_liste();
    	en_tete();
      team = 1;
  		/*boucle pour un tour*/
      while(!hors_liste()){

        detection_etat(pt_m);
        hp_team1=get_hp_team(1);
        hp_team2=get_hp_team(2);
        /*condition d'arret de la partie*/
        if (hp_team1<=0 || hp_team2<=0){
          partie_en_cours=0;
          break;
        }
        valeur_elt(&tmp);
        if(!strcmp(tmp->pp, "👽")){    /*  /!\   probleme ici pour les poisons et autre qui font le double des degats du au delimiteur */
          team = 2;
        } 
        else if(tmp->pv>0 && team == ma_team) {

          afficher_map(pt_m);
    		  info_personnage(tmp);
          /*printf("infos affiches\n");*/
    		  action_client = menu_choix(tmp, pt_m, web);
    		  if(web)
    		  	send_action(to_server_socket, action_client);
    		  
        }
        else if (tmp->pv>0 && team != ma_team){
        	afficher_map(pt_m);
    		  info_personnage(tmp);
        	//enregistrement d'une action
  				action_t * action_serv = malloc(sizeof(action_serv));
					recive_action(to_server_socket, action_serv, pt_m);
				}
        suivant();
      }

    }
    detection_etat(pt_m);
  	afficher_map(pt_m);

	  if (hp_team1>hp_team2)
	    	gg(serveur_id);    
	  else
	    gg(client_id);

	  free(action_serv);
	  free(action_client);
    

  }
  


	/* fermeture de la connexion */
	shutdown(to_server_socket,2);
	close(to_server_socket);
	return 0;
}


void menu_online(carte_t * pt_m){
	int x;

	system("clear");
	printf(MAG"Partie en reseau\n"RESET);
	
	do{
		printf("1) Heberger un partie \n2) Rejoindre une partie\n3) Quitter\n\n");
		//x = getchar();
		scanf("%d", &x);
	}while(x > 3 || x < 1);

	if (x==1)
		hosting_game(pt_m);
	else if (x==2)
		joining_game(pt_m);
	else
		printf(MAG"retour\n"RESET);
	printf("###\n");
}

//gcc -o reseau reseau.c -lcrypto

/*pensser à une sortie si on initialise un perso 
en dehors de la map par faute de taille*/
/*verifier les fichiers ouverts*/

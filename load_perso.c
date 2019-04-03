#include "fonctions.h"

//#define p_save ((const unsigned char * )"./data/p_save.txt")
//char * p_save = "./p_save.txt";

void aff_all(char * p_save){

	FILE * file;
	file = fopen(p_save, "r");
	char c;

	printf("\n\n**************\n Affichage : \n**************\n\n");
	fscanf(file, "%c",&c);

	while (!feof(file)){
		printf("%c",c);
		fscanf(file, "%c",&c);

	}
	fclose(file);
}

int dbl_len(char *s){
	int i=0;
	while(*s){
		i++;
		s++;
	}
	return(i);
}

void dbl_cpy(char ** d, char * q){
  int i=0;
  char * d2 = malloc(sizeof(char) * dbl_len(q)+1);

  while (q[i]!='\0'){
    d2[i] = q[i];
    i++;
  }
  d2[++i] = '\0';
	//memset(d, '\0', sizeof(d));
  //free(*d);

  *d=d2;

}

char * get_nom(char * p_save,char *s, int index){

	FILE * file;
	file = fopen(p_save, "r");
	char x = ' ';
  int ligne;
	char trace[100];
  char * _nom;
  const char del[2] = "-";
	int i=0;

  //choppe le 0
	fscanf(file, "%d", &ligne);

	//cherche la bonne ligne
	while(ligne != index && !feof(file)){
		while(x != '\n'){
			fscanf(file, "%c", &x);
	      if (feof(file)){
	        return("personnage n'existe pas");
	      }
		}
		fscanf(file, "%d", &ligne);
    fscanf(file, "%c", &x);
	}

  fscanf(file, "%c", &x); // passe le \n <-non
  fgets (trace, 100, file); // récupere la ligne

  _nom = strtok(trace, del); // on isole le nom
	strncpy(s,_nom,35);

	fclose(file);
  return(s);
}

int c2i(char c){ return(c-'0'); }

char i2c(int i){ return(i+'0'); }

int is_digit(char c){
	if (c>='0' && c<='9'){
		return(1);}
	return(0);
}

int s2i(char *s){

	int t = strlen(s);
	 int value = 0;
	  int neg = 1;
       int i=0;

	if (s[0]=='-'){
		neg=-1;
		i++;
	}

	for(; i<t && is_digit(s[i]) ; i++){
		value*=10;
		value+=c2i(s[i]);
	}

	return (value*neg);
}

int get_champ(char * p_save, int index,int * px, int * py, int * classe ){

	FILE * file;
	 file = fopen(p_save, "r");
	char x;
	int i=0,champ=0;
	char s[15];
	int monCul=0;
	int a,b,c;
	//prend le 0
	fscanf(file, "%d", &i);

	//cherche la ligne
	while(i != index && !feof(file)){
		while(x != '\n'){
			fscanf(file, "%c", &x);
			if (feof(file)){
	      printf("%s\n","personnage n'existe pas" );
				return(2);
      }
		}

		fscanf(file, "%d", &i);
		fscanf(file, "%c", &x);
	}

		//cherche le 1er champ
	while(x != '-')
		fscanf(file, "%c", &x);
	fscanf(file, "%c", &x);
	while(x != '-')
		fscanf(file, "%c", &x);
	//saute l'espace
	fscanf(file, "%c", &x);
	//prend les trois champs de type int
	fscanf(file, "%d ", px);
	fscanf(file, "%d ", py);
	fscanf(file, "%d ", classe);

	fclose(file);

	return(0);
}

int get_nb_pers(char * p_save, int * nb_pers){

	FILE * file;
	file = fopen(p_save, "r");

	fscanf(file, "%d", nb_pers );
	fscanf(file, "%d", nb_pers );

	fclose(file);

	return(*nb_pers);

}
//fonction qui envoie les infos perssus dans le fichier vers 
void gogo_powerRanger(int px, int py, char * nom, int classe, carte_t * pt_m){
	personnage_t * Lucatiel = malloc(sizeof(personnage_t));
  init_hero(Lucatiel, px, py, nom, pt_m, classe);

}

void quit_quick(carte_t * pt_m){
	detruire_liste();
  map_detruire(&pt_m);
  afficher_liste();
  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);

}

void load_perso(carte_t * pt_m){
	//printf("donner un niveau (1 a 9)\n");
	int i = 1;
	printf("%s %s\n", RED"p_save.txt"RESET,"a ete charge\n");
	char * p_save = "save/p_save.txt";

	int px, py, classe, nb_pers;
	char * nom = malloc(sizeof(char)*35+1);
	get_nb_pers(p_save, &nb_pers);
	//printf("nb pers : %d\n\n", nb_pers);
	for(; i<nb_pers+1; i++){
		get_nom(p_save, nom, i);
		get_champ(p_save, i, &px, &py, &classe);
	  //printf("%s -> px:%d py:%d classe:%d\n", nom, px, py, classe);

	  gogo_powerRanger(px, py, nom, classe, pt_m);
	}

	free(nom);
}


/* nom px py classe */











/**/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


//#define p_save ((const unsigned char * )"./data/p_save.txt")
char * p_save = "./p_save.txt";

void aff_all(){

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
  free(*d);
  *d=d2;

}

char * get_nom(char **s, int index){

	FILE * file;
	file = fopen(p_save, "r");
	char x= ' ';
  int _vide = 0;
  int ligne;
	char trace[100];
  char * token;
  const char del[2] = "-";
	int i=0;

  //choppe le 0
	fscanf(file, "%d", &ligne);

	//cherche la bonne ligne
	while(ligne != index && !feof(file)){
		while(x != '\n'){
			fscanf(file, "%c", &x);
      if (feof(file)){
        _vide=1;
        break;
      }

		}
    if(_vide)
      return("personnage n'existe pas");
    
		fscanf(file, "%d", &ligne);
    fscanf(file, "%c", &x);
	}

  fscanf(file, "%c", &x); // passe le \n
  fgets (trace, 50, file); // récupere la ligne
  
  token = strtok(trace, del);

  printf("%s\n", token);
  dbl_cpy(s, token);

  return(token);

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

int get_champ(int index,int stat ){

	FILE * file;
	 file = fopen(p_save, "r");
	char x;
	int i=0;
	char s[15];
	int monCul=0;

	fscanf(file, "%d", &i);

	//cherche la ligne
	while(i != index && !feof(file)){
		while(x != '\n'){
			fscanf(file, "%c", &x);
		}
		fscanf(file, "%d", &i);
	}

	//cherche le champ
	for(int champ=0 ; champ < stat-1; champ ++){
		fscanf(file, "%s ", s);
	}

	fscanf(file, "%d", &monCul);
	return(monCul);
}

void * get_line(char *s, int index){

	FILE * file;
	file = fopen(p_save, "r");
	char x= ' ';
  int _vide = 0;
  int ligne;
	char trace[100];
  char * token;
  const char del[2] = "-";
	int i=0;

  //choppe le 0
	fscanf(file, "%d", &ligne);


	//cherche la bonne ligne
  printf("on a trouvé %d %d\n", index, ligne );
	while(ligne != index && !feof(file)){
		while(x != '\n'){
			fscanf(file, "%c", &x);
      if (feof(file)){
        _vide=1;
        break;
      }

		}
    if(_vide)
      return("personnage n'existe pas");

    //fscanf(file, "%c", &x);
		fscanf(file, "%d", &ligne);
    fscanf(file, "%c", &x);
    printf("->%d\n",ligne );
	}


  fscanf(file, "%c", &x);
  //fscanf(file, "%[^'\n']", &trace);
  fgets (trace, 50, file);
  printf("%s\n", trace);
  token = strtok(trace, del);

  //token = strtok(NULL, s);
  printf("%s\n", token);

  return(token);

	//printf("test nom : %s\n", s);
}


int main(){

  //aff_all();
  char * s;
  get_nom(&s, 2);
  printf("\n-> %s\n", s);




  return(0);
}

/* nom force PV PV_MAX px py pm classe */














/**/

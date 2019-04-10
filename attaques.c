#include "fonctions.h"
#include "personnage.h"


/*
fonctions à faire :
  - rappel, qui rend des pv à un perso mort
  - charge, qui fait des degats sur la case en face
  -

*/

//prend un x et un y et les envoient dans les fonctions d'attaques
void getXY(personnage_t * p, void * m, void f_cb(void * pp, void * map, int xi, int yi)){

  int x=0,y=0,i=0;

  if(!(f_cb == &tourbilol_cb || f_cb == &jet_de_sable_cb || f_cb == &shield_cb || f_cb == &arakiri_cb )){
    printf("Donner la position\n");
    do{
      if(i >=1)
        printf("Error, sortie de map !!!");
      printf("X :");
      scanf("%d",&x);
      printf("Y :");
      scanf("%d",&y);
      i++;
    }while((x <0 || x >N) || (y <0 || y >N));
  }
  else{
    x = p->px;
    y = p->py;
  }
  f_cb(p, m, x, y);

  /*on pourrait récupérer le code d'erreur de la fonction, en mode :
  si la renge ne le permet pas on revien ici et on recommence*/
}

void coup(personnage_t * personnage,int degats){
  if(personnage->est_shield){
    personnage->est_shield -= degats;
    if(personnage->est_shield<0){
      personnage->pv+=personnage->est_shield;
      personnage->est_shield=0;
    }
  }
  else
    personnage->pv -= degats;
}

int range_detection(personnage_t *_personnage,int range,int x,int y){
  int range_X,range_Y,range_Total;

  range_X = fabs(_personnage->px) - fabs(x);
  range_Y= fabs(_personnage->py) - fabs(y);
  range_Total = fabs(range_X) + fabs(range_Y);

  if(range >= range_Total){
    return 1;
  }
  else{
    return 0;
  }
}

void boule_de_feu(personnage_t *_personnage, carte_t * pt_m, int x, int y){ // mage noir, mage blanc

  int dommage = 115;
  int range = 5;

  if(pt_m->map[x][y]->personnage != NULL){
    if(range_detection(_personnage,range,y,x)){
      printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, pt_m->map[x][y]->personnage->nom);
      //pt_m->map[x][y]->personnage->pv -= _personnage->force + dommage;
      coup(pt_m->map[x][y]->personnage,  _personnage->intel + dommage);
      printf(YEL"%s prend %d dommages\n"RESET, pt_m->map[x][y]->personnage->nom, _personnage->force + dommage );
    }
    else
      printf(YEL"%s\n"RESET,"Range insuffisante");
  }
}

void boule_de_feu_cb(void *_personnage, void * pt_m, int x, int y){
  boule_de_feu(_personnage, pt_m, x, y);
}

/* fonction statique */
static void fuite(personnage_t *_personnage, carte_t * pt_m,int x,int y){

  pt_m->map[_personnage->px][_personnage->py]->personnage = NULL;

  _personnage->px =  x;
  _personnage->py =  y;

  while(  pt_m->map[_personnage->px][_personnage->py]->personnage != NULL){
    _personnage->px =  x + 1;
    _personnage->py =  y + 1;

  }
    pt_m->map[_personnage->px][_personnage->py]->personnage = _personnage;
}

void soin(personnage_t *_personnage, carte_t * pt_m, int x, int y){
  int soin = 160;
  int range = 4;

  if(pt_m->map[x][y]->personnage != NULL){
    if((range_detection(_personnage,range,y,x))){
      printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, pt_m->map[x][y]->personnage->nom);
      pt_m->map[x][y]->personnage->pv += soin;
      printf(YEL"%s se soigne de %d points de vies\n"RESET, pt_m->map[x][y]->personnage->nom, soin );
    }
    else
      printf(YEL"%s\n"RESET,"Range insuffisante");
  }
}
void soin_cb(void *_personnage, void * pt_m, int x, int y){
  soin(_personnage,pt_m,x,y);
}

void cure(personnage_t *_personnage, carte_t * pt_m, int x, int y){
  int range = 4;

  if(pt_m->map[x][y]->personnage != NULL){
    if((range_detection(_personnage,range,y,x))){
      printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, pt_m->map[x][y]->personnage->nom);
      pt_m->map[x][y]->personnage->est_empoisone = 0;
      pt_m->map[x][y]->personnage->est_enfeu = 0;

      printf(YEL"%s est gueri de ses alterations d'etats\n"RESET, pt_m->map[x][y]->personnage->nom);
    }
    else
    printf(YEL"%s\n"RESET,"Range insuffisante");
  }
}
void cure_cb(void *_personnage, void * pt_m, int x, int y){
  cure(_personnage, pt_m, x, y);
}

void toxicite(personnage_t * personnage,carte_t * pt_m, int x, int y){
  int range = 6;

  if(pt_m->map[x][y]->personnage != NULL){
    if(range_detection(personnage,range,y,x)){
      printf(YEL"\n%s cible %s \n"RESET, personnage->nom, pt_m->map[x][y]->personnage->nom);
      pt_m->map[x][y]->personnage->est_empoisone=1;
      printf(YEL"%s est devenu toxique\n"RESET, pt_m->map[x][y]->personnage->nom);

    }
    else
      printf(YEL"%s\n"RESET,"Range insuffisante");
  }
}
void toxicite_cb(void * personnage,void * pt_m, int x, int y){
  toxicite(personnage,pt_m,x,y);
}
/*y a vraiment rien qui va avec cette fonction...*/
void tourbilol(personnage_t * personnage,carte_t * pt_m, int x, int y){ /* #pasfini */

  int degats = 100;
  printf(YEL"%s execute un tourbilol !\n"RESET, personnage->nom);


  if(pt_m->map[personnage->px+1][personnage->py]->personnage != NULL){
    coup(pt_m->map[personnage->px+1][personnage->py]->personnage, personnage->force + degats);
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px+1][personnage->py]->personnage->nom);

  }
  if(pt_m->map[personnage->px+1][personnage->py+1]->personnage != NULL){
    //coup(pt_m->map[personnage->px+1][personnage->py], personnage->force + degats);
    pt_m->map[personnage->px+1][personnage->py+1]->personnage->pv -= personnage->force + degats;
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px+1][personnage->py+1]->personnage->nom);
  }
  if(pt_m->map[personnage->px][personnage->py+1]->personnage != NULL){
    pt_m->map[personnage->px][personnage->py+1]->personnage->pv -= personnage->force + degats;
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px][personnage->py+1]->personnage->nom);

  }
  if(pt_m->map[personnage->px-1][personnage->py]->personnage != NULL){
    pt_m->map[personnage->px-1][personnage->py]->personnage->pv -= personnage->force + degats;
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px-1][personnage->py]->personnage->nom);

  }
  if(pt_m->map[personnage->px-1][personnage->py-1]->personnage != NULL){
    pt_m->map[personnage->px-1][personnage->py-1]->personnage->pv -= personnage->force + degats;
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px-1][personnage->py-1]->personnage->nom);
  }
  if(pt_m->map[personnage->px][personnage->py-1]->personnage != NULL){
    pt_m->map[personnage->px][personnage->py-1]->personnage->pv -= personnage->force + degats;
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px][personnage->py-1]->personnage->nom);
  }
  if(pt_m->map[personnage->px+1][personnage->py-1]->personnage != NULL){
    pt_m->map[personnage->px+1][personnage->py-1]->personnage->pv -= personnage->force + degats;
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px+1][personnage->py-1]->personnage->nom);
  }
  if(pt_m->map[personnage->px-1][personnage->py+1]->personnage != NULL){
    pt_m->map[personnage->px-1][personnage->py+1]->personnage->pv -= personnage->force + degats;
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px-1][personnage->py+1]->personnage->nom);
  }
}

void tourbilol_cb(void * personnage,void * pt_m, int x, int y){
  tourbilol(personnage,pt_m,x,y);
}

void shield(personnage_t * personnage,carte_t * pt_m, int x, int y){

  int efficacite = 100;

  printf(YEL"%s s'ajoute %d d'armure !\n"RESET, personnage->nom,efficacite);

  personnage->est_shield += efficacite;

  printf(YEL"%s a maintenant %d d'armure\n"RESET, personnage->nom,personnage->est_shield);

}
void shield_cb(void * personnage,void * pt_m, int x, int y){
  shield(personnage,pt_m, x, y);
}

void fait_ton_greu(personnage_t * _personnage,carte_t * pt_m, int x, int y){ /* pas fini */ /* need detection hors map*/ /*ERREUR DE SEGMENTATION */
  int degats = 50;
  int fear = 2;
  int range = 5;
  int l,h; //coefficients de hauteur/largeur


  printf(YEL"%s fait son greu !!\n"RESET, _personnage->nom);
  if(pt_m->map[x][y]->personnage != NULL && pt_m->map[x][y]->personnage != _personnage){
    if(range_detection(_personnage,range,y,x)){
        coup(pt_m->map[x][y]->personnage,_personnage->force + degats);

        //verification de la position de la cible
        if(y == _personnage->py){
          h=0;
          if(x < _personnage->px)
            l=-1;
          else
            l=1;
        }
        else if(y > _personnage->py){
          h=1;
	        if(x == _personnage->px)
	          l=0;
	        else if(x > _personnage->px)
	          l=1;
	        else/*(x < personnage->px)*/
	          l =-1;
        }
        else if(y < _personnage->py){
	        h=-1;
	        if(x == _personnage->px)
	          l=0;
	        else if(x > _personnage->px)
	          l=1;
	        else/*(x < personnage->px)*/
	          l=-1;
        }

      int xn = x+(fear*l); //nouvelle valeur de x de la cible (après fear)
      int yn = y+(fear*h);//nouvelle valeur de y de la cible (après fear)

      //verification de sortie de map
      if(xn < 0)
        xn = 0;
      if(xn > pt_m->nb_dalles_x-1)
        xn = pt_m->nb_dalles_x-1;
      if(yn < 0)
        yn = 0;
      if(yn > pt_m->nb_dalles_y-1)
        yn = pt_m->nb_dalles_y-1;

      fuite(pt_m->map[x][y]->personnage,pt_m,xn,yn);

      printf(YEL"%s a pris %d points de degats !\n"RESET, pt_m->map[xn][yn]->personnage->nom,degats);
      printf(YEL"%s a pris peur et s'enfuit !\n"RESET, pt_m->map[xn][yn]->personnage->nom);

    }
    else
      printf(YEL"%s\n"RESET,"Range insuffisante");

    }else
      printf(YEL"%s echoue son greu..\n"RESET, _personnage->nom);
}

void fait_ton_greu_cb(void * _personnage,void * pt_m, int x, int y){
  fait_ton_greu(_personnage,pt_m,x,y);
}

/*------------------------------------------------------------------------------------------*/

void deplacement(personnage_t *_personnage, carte_t * pt_m, int x, int y){

  int range = 6;

  if(pt_m->map[x][y]->personnage == NULL){
    if(range_detection(_personnage,range,y,x)){
    	pt_m->map[_personnage->px][_personnage->py]->personnage = NULL;
      _personnage->px =  x;
      _personnage->py =  y;
      pt_m->map[_personnage->px][_personnage->py]->personnage = _personnage;
    }
    else
      printf(YEL"%s\n"RESET,"Range insuffisante");
  }
  else{
    printf("\nIl y a déja un personnage sur cette case !!\n");
    //return 10;  permet de pas passer el tour du joueur si il se trompe
  }
}
void deplacement_cb(void *_personnage, void * pt_m, int x, int y){
  deplacement(_personnage, pt_m, x, y);
}

void summon(personnage_t *_personnage, carte_t * pt_m, int x, int y){

  int range = 5;

  if(pt_m->map[x][y]->personnage == NULL){
    if(range_detection(_personnage,range,y,x)){
      personnage_t * ptitsac = malloc(sizeof(personnage_t));
      //compte le nb de perso dans la liste puis:
      init_hero(ptitsac,10, x, y, "sac", pt_m, sac);                         // là.
    }else
      printf(YEL"%s\n"RESET,"Range insuffisante");
  }else
    printf("\nLa case est occupée !\n");
}
void summon_cb(void *_personnage, void * pt_m, int x, int y){
  summon(_personnage, pt_m, x, y);
}

void sheep(personnage_t *_personnage, carte_t * pt_m, int x, int y){
  int range = 5;

  if(pt_m->map[x][y]->personnage != NULL){
    if(range_detection(_personnage,range,y,x)){
      free(pt_m->map[x][y]->personnage->pp);
      char * _pp = "🐑";
      pt_m->map[x][y]->personnage->pp = malloc(sizeof(char)*strlen(_pp)+1);
      strcpy(pt_m->map[x][y]->personnage->pp,"🐑");
      pt_m->map[x][y]->personnage->est_sheep = 1;
      printf("\ncc :%d\n",pt_m->map[x][y]->personnage->est_sheep);
    }else
      printf(YEL"%s\n"RESET,"Range insuffisante");
  }
  printf("\nIl n'y a personne sur cette case :\n");
}
void sheep_cb(void *_personnage, void * pt_m, int x, int y){
  sheep(_personnage, pt_m, x ,y);
}

void detection_etat(carte_t * pt_m){
  personnage_t * ex;
  personnage_t * stockage;
  valeur_elt(&ex);
  en_tete();

  while(!hors_liste()){
    valeur_elt(&stockage);

    if(stockage->pv <= 0){
      if ((strcmp(stockage->pp,"👽")) && (strcmp(stockage->pp,"💀") ) ){
        free(stockage->pp);
        stockage->pp = NULL;

        //printf("\ncc2 :%s\n",stockage->pp);
        char * pp = "💀";

        //printf("\ncc3 :%s\n",stockage->pp);
        stockage->pp = malloc(sizeof(char)*strlen(pp));
        //printf("\ncc4 :%s\n",stockage->pp);

        strcpy(stockage->pp,pp);
        printf(YEL "\n%s est mort\n" RESET,stockage->nom);

        stockage->est_mort = 1;
        stockage->pv = 0;
      }

    }
    if (stockage->est_empoisone){
      coup(stockage, 11);
    }
    /*mystiquement cette condition est maudite*/
    /*if ( pt_m->map[stockage->px][stockage->py]->land == 3 ){
      stockage->est_enfeu = 1;
    }*/
    if (stockage->est_enfeu){
      coup(stockage, 13);
    }
    if ( stockage->est_aveugle > 0 ){
    stockage->est_aveugle = (stockage->est_aveugle) - 1;
      printf("\n%s est aveuglé il lui reste %d tour(s) avant de pouvoir attaquer !\n",stockage->nom, stockage->est_aveugle);
    }

    suivant();
  }
  backdash(ex);
}




void arakiri(personnage_t * personnage, carte_t * pt_m, int x, int y){ //   C good

int i;
int j;
int range = 2;

    for(i = x-range; i < x+range ; ++i){ // collision_carre
      for(j = y-range; j < y+range ; ++j){
        if(i>=0  && i<N && j<N && j>=0){
          if(pt_m->map[i][j]->personnage != NULL)
            coup(pt_m->map[i][j]->personnage, 50);
          if(pt_m->map[i][j]->land != 2)
            pt_m->map[i][j]->land = 3;
          else{
            pt_m->map[i][j]->land = 1;
          }
        }
      }
    }
}

void arakiri_cb(void * personnage, void * pt_m, int x, int y){
  arakiri( personnage,pt_m,x,y);
}


void jet_de_sable(personnage_t * personnage, carte_t * pt_m, int x, int y){

int range = 4;
if(pt_m->map[x][y]->personnage != NULL){
  if(range_detection(personnage,range,y,x)){
    pt_m->map[x][y]->personnage->est_aveugle = 3;

}else
  printf(YEL"%s\n"RESET,"Range insuffisante");
}else
printf("\n Il n'y a personne sur cette case !\n");

}

void jet_de_sable_cb(void * personnage,void * pt_m, int x, int y){
  jet_de_sable(personnage,pt_m, x, y);
}

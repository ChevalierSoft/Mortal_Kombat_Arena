#include "fonctions.h"
#include "personnage.h"

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
/* fonction statique */
void fuite(personnage_t *_personnage, carte_t * pt_m,int x,int y){

  pt_m->map[_personnage->px][_personnage->py]->personnage = NULL;


  _personnage->px =  x;
  _personnage->py =  y;

  pt_m->map[_personnage->px][_personnage->py]->personnage = _personnage;


}

void coup(personnage_t * personnage,int degats){
  personnage->pv -= degats;
}


void boule_de_feu_cb(void *_personnage, void * pt_m){
  boule_de_feu(_personnage, pt_m);
}

void boule_de_feu(personnage_t *_personnage, carte_t * pt_m){ // mage noir, mage blanc

  int x,y;
  int dommage = 115;
  int range = 5;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(pt_m->map[x][y]->personnage != NULL){
    if(range_detection(_personnage,range,y,x)){
      printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, pt_m->map[x][y]->personnage->nom);
      pt_m->map[x][y]->personnage->pv -= _personnage->force + dommage;
      printf(YEL"%s prend %d dommages\n"RESET, pt_m->map[x][y]->personnage->nom, _personnage->force + dommage );
    }
    else
      printf(YEL"%s\n"RESET,"Range insuffisante");
  }
}

void soin_cb(void *_personnage, void * pt_m){
  soin(_personnage,pt_m);
}

void soin(personnage_t *_personnage, carte_t * pt_m){ //mage blanc
  int x,y;
  int soin = 160;
  int range = 4;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

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
void cure_cb(void *_personnage, void * pt_m){
  cure(_personnage, pt_m);
}
void cure(personnage_t *_personnage, carte_t * pt_m){
  int x,y;
  int range = 4;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(pt_m->map[x][y]->personnage != NULL){
    if((range_detection(_personnage,range,y,x))){
      printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, pt_m->map[x][y]->personnage->nom);
      pt_m->map[x][y]->personnage->est_empoisone = 0;
      pt_m->map[x][y]->personnage->est_enfeu = 0;

      printf(YEL"%s est gueri de ses alterations d'etat\n"RESET, pt_m->map[x][y]->personnage->nom);
    }
    else
    printf(YEL"%s\n"RESET,"Range insuffisante");
  }
}

void toxicite(personnage_t * personnage,carte_t * pt_m){
  int x,y;
  int range = 6;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

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

void toxicite_cb(void * personnage,void * pt_m){
  toxicite(personnage,pt_m);
}

void tourbilol(personnage_t * personnage,carte_t * pt_m){ /* pas fini */ /* need detection hors map*/

  int degats = 100;
  printf(YEL"%s execute un tourbilol !\n"RESET, personnage->nom);


  if(pt_m->map[personnage->px+1][personnage->py]->personnage != NULL){
    pt_m->map[personnage->px+1][personnage->py]->personnage->pv -= personnage->force + degats;
    printf(YEL"%s a ete blesse\n"RESET, pt_m->map[personnage->px+1][personnage->py]->personnage->nom);

  }
  if(pt_m->map[personnage->px+1][personnage->py+1]->personnage != NULL){
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

void tourbilol_cb(void * personnage,void * pt_m){
  tourbilol(personnage,pt_m);
}

void shield(personnage_t * personnage,carte_t * pt_m){

  int efficacite = 50;

  printf(YEL"%s se rajoute %d de shield !\n"RESET, personnage->nom,efficacite);

  personnage->est_shield += efficacite;

  printf(YEL"%s est maintenant à %d de shield\n"RESET, personnage->nom,personnage->est_shield);

}

void shield_cb(void * personnage,void * pt_m){
  shield(personnage,pt_m);
}

void fait_ton_greu(personnage_t * personnage,carte_t * pt_m){ /* pas fini */ /* need detection hors map*/ /*ERREUR DE SEGMENTATION */
  int degats = 50;
  int fear = 2;
  int x,y;
  int l,h; //coefficients de hauteur/largeur

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  printf(YEL"%s fait son greu !!\n"RESET, personnage->nom);
  if(pt_m->map[x][y]->personnage != NULL && pt_m->map[x][y]->personnage != personnage){
    coup(pt_m->map[x][y]->personnage,personnage->force + degats);

    //verification de la position de la cible
    if(y == personnage->py){
      h=0;
      if(x < personnage->px)
        l=-1;
      else if(x > personnage->px)
        l=1;
    }
    else if(y > personnage->py){
      h=1;
      if(x == personnage->px)
        l=0;
      else if(x > personnage->px)
        l=1;
      else if(x < personnage->px)
        l =-1;
    }
    else if(y < personnage->py){
      h=-1;
      if(x == personnage->px)
        l=0;
      else if(x > personnage->px)
        l=1;
      else if(x < personnage->px)
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
    printf(YEL"%s echoue son greu..\n"RESET, personnage->nom);

}

void fait_ton_greu_cb(void * personnage,void * pt_m){
  fait_ton_greu(personnage,pt_m);
}

/*------------------------------------------------------------------------------------------*/

int deplacement(personnage_t *_personnage, carte_t * pt_m){
  int x,y;

  printf("\nCoordonnées de déplacement :");
  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);
  pt_m->map[_personnage->px][_personnage->py]->personnage = NULL;

  _personnage->px =  x;
  _personnage->py =  y;
  pt_m->map[_personnage->px][_personnage->py]->personnage = _personnage;
}
/*
void jet_de_sable(){

}*/
/*
void arakiri(personnage_t * personnage, carte_t * pt_m){
  int range = 2;

  if(pt_m->map[personnage->px + 1][personnage->py]->personnage != NULL){
    if(range_detection(personnage,range,y,personnage->px + 1)){
      printf(YEL"\n%s cible %s \n"RESET, personnage->nom, pt_m->map[x][y]->personnage->nom);
      pt_m->map[x][y]->personnage->pv -= personnage->force + dommage;
      printf(YEL"%s prend %d dommages\n"RESET, pt_m->map[x][y]->personnage->nom, personnage->force + dommage );
    }
    else
      printf("\nRange insuffisante.\n");
  }

}
*/

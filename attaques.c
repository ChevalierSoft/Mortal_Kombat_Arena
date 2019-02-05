/*extern*/
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

void boule_de_feu_cb(void *_personnage, void * pt_m){
  boule_de_feu(_personnage, pt_m);
}
void boule_de_feu(personnage_t *_personnage, carte_t * pt_m){ // mage noir, mage blanc

  int x,y;
  int dommage = 2;
  int range = 5;

  printf("X :");
  scanf("%d",&x);//1
  printf("Y :");
  scanf("%d",&y);//2

  if(pt_m->map[x][y]->personnage != NULL){
    if((range_detection(_personnage,range,y,x) == 1)){
      printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, pt_m->map[x][y]->personnage->nom);
      pt_m->map[x][y]->personnage->pv -= _personnage->force + dommage;
      printf(YEL"%s prend %d dommages\n"RESET, pt_m->map[x][y]->personnage->nom, _personnage->force + dommage );
    }
    else
      printf("\nRange insuffisante.\n");
  }
}

void soin_cb(void *_personnage, void * pt_m){
  soin(_personnage,pt_m);
}

void soin(personnage_t *_personnage, carte_t * pt_m){ //mage blanc
  int x,y;
  int soin = 2;
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
      printf("\nRange insuffisante.\n");
  }
}

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

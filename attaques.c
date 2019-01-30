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

void boule_de_feu(personnage_t *_personnage,carellage_t map[N][N]){ // mage noir, mage blanc

  int x,y;
  int dommage = 2;
  int range = 5;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(map[y][x].personnage != NULL){
    if((range_detection(_personnage,range,x,y) == 1)){
      printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, map[y][x].personnage->nom);
      map[y][x].personnage->pv -= _personnage->force + dommage;
      printf(YEL"%s prend %d dommages\n"RESET,map[y][x].personnage->nom, _personnage->force + dommage );
    }
    else
        printf("\nRange insuffisante.\n");
  }
}

void soin(personnage_t *_personnage,carellage_t map[N][N]){ //mage blanc
  int x,y;
  int soin = 2;
  int range = 4;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(map[y][x].personnage != NULL){
    if((range_detection(_personnage,range,x,y) == 1)){
      printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, map[y][x].personnage->nom);
      map[y][x].personnage->pv -= _personnage->pv + soin;
      printf(YEL"%s se soigne de %d points de vies\n"RESET, map[y][x].personnage->nom, _personnage->pv + soin );
    }
    else
        printf("\nRange insuffisante.\n");
  }
}

int deplacement(personnage_t *_personnage, carellage_t map[N][N]){
  int x,y;

  printf("\nCoordonnées de déplacement :");
  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  map[_personnage->py][_personnage->px].personnage = NULL;

  _personnage->px =  x;
  _personnage->py =  y;

  map[_personnage->py][_personnage->px].personnage = _personnage ;
}

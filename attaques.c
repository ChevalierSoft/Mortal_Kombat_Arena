/*extern*/
#include "fonctions.h"
#include "personnage.h"

void boule_de_feu(personnage_t *_personnage,carellage_t map[N][N]){

  int x,y;
  int dommage = 2;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(map[y][x].personnage != NULL){
    printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, map[y][x].personnage->nom);
    map[y][x].personnage->pv -= _personnage->force + dommage;
    printf(YEL"%s prend %d dommages\n"RESET,map[y][x].personnage->nom, _personnage->force + dommage );
  }

}

void soin(personnage_t *_personnage,carellage_t map[N][N]){
  int x,y;
  int soin = 2;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(map[y][x].personnage != NULL){
    printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, map[y][x].personnage->nom);
    map[y][x].personnage->pv -= _personnage->pv + soin;
    printf(YEL"%s se soigne de %d points de vies\n"RESET, map[y][x].personnage->nom, _personnage->pv + soin );

  }
}

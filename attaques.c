/*extern*/
#include "fonctions.h"
#include "personnage.h"

void boule_de_feu(personnage_t *_personnage,carte_t * pt_m){

  int x,y;
  int dommage = 2;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(pt_m->map[x][y]->personnage != NULL){
    printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, pt_m->map[x][y]->personnage->nom);
    pt_m->map[x][y]->personnage->pv -= _personnage->force + dommage;
    printf(YEL"%s prend %d dommages\n"RESET,pt_m->map[x][y]->personnage->nom, _personnage->force + dommage );
  }

}

void soin(personnage_t *_personnage,carte_t * pt_m){
  int x,y;
  int soin = 2;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(pt_m->map[x][y]->personnage != NULL){
    printf(YEL"\n%s cible %s \n"RESET, _personnage->nom, pt_m->map[x][y]->personnage->nom);
    pt_m->map[x][y]->personnage->pv -= _personnage->pv + soin;
    printf(YEL"%s se soigne de %d points de vies\n"RESET, pt_m->map[x][y]->personnage->nom, _personnage->pv + soin );

  }
}

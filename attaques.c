/*extern*/
#include "fonctions.h"
#include "personnage.h"

void boule_feux(mage_t *m,carellage_t n[N][N]){

  int x,y;
  int dommage = 2;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(n[y][x].personnage != NULL){
    printf("\n%s est ciblé\n",n[y][x].personnage->nom);
    n[y][x].personnage->pv -= m->force + dommage;
  }

}

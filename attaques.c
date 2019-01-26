/*extern*/
#include "fonctions.h"
#include "personnage.h"

void boule_de_feu(mage_t *m,carellage_t n[N][N]){

  int x,y;
  int dommage = 2;

  printf("X :");
  scanf("%d",&x);
  printf("Y :");
  scanf("%d",&y);

  if(n[y][x].personnage != NULL){
    printf(YEL"\n%s cible %s \n"RESET, m->nom, n[y][x].personnage->nom);
    n[y][x].personnage->pv -= m->force + dommage;
    printf(YEL"%s prend %d dommages\n"RESET, n[y][x].personnage->nom, m->force + dommage );
  }

}

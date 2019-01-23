#include "fonctions.h"
#include "personnage.h"
#include "couleur.h"

void afficher_mage(mage_t * marvin){
  printf("\npv :%d\n", marvin->pv);
  printf("force :%d\n",marvin->force);
  printf("px :%d\n", marvin->px);
  printf("py :%d\n", marvin->py);
  printf("nom :%s\n", marvin->nom);
  printf("Image du perso :%s\n", marvin->pp);

}

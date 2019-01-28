#include "fonctions.h"
#include "personnage.h"


#define N 10

int main(int argc, char const *argv[]) {
  printf(RED"\n++++++++++++++++++++ M K Arena ++++++++++++++++++++\n"RESET);
  carte_t * pt_m;

  //on crée le plateau de jeu (#ez)
  charger_partie(pt_m);
  afficher_map(pt_m);

  //on crée un mage de chiansse ici (c'est zéro mais, mais.)
  //mage_t * marvin = malloc(sizeof(mage_t)); // creer une structure marvin qui est un mage
  //_mage, _force,  _PV, _px, _py,  _pm,  _nom, *_pp
  /*init_mage(marvin,1,10,1,2,1,"marvin","🔥",pt_m); // on initit la structure marvin avec ses stats
  //un deuxieme
  mage_t * Zeddicus_Zul_Zorander = malloc(sizeof(mage_t));
  init_mage(Zeddicus_Zul_Zorander,2,11,3,4,2,"Zeddicus Zul'Zorander","🔮",map1);*/

  //kombat(marvin, Zeddicus_Zul_Zorander,map1);

  free(pt_m);
  pt_m = NULL;
  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);

  return 0;

}

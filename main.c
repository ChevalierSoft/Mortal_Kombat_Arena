#include "fonctions.h"
#include "personnage.h"


#define N 10

int main(int argc, char const *argv[]) {
  printf(RED"\n++++++++++++++++++++ M K Arena ++++++++++++++++++++\n"RESET);
  carte_t * pt_m= malloc(sizeof(carte_t));

  //on crée le plateau de jeu (#ez)
  
  charger_partie(pt_m);


  afficher_map(pt_m);

  //on crée un mage de chiansse ici (c'est zéro mais, mais.)
  personnage_t * marvin = malloc(sizeof(personnage_t)); // creer une structure marvin qui est un mage
  //_mage, _force,  _PV, _px, _py,  _pm,  _nom, *_pp
  init_hero(marvin,1,10,1,2,1,"marvin","🔥",pt_m,mage_blanc); // on initit la structure marvin avec ses stats
  //un deuxieme
  personnage_t * Zeddicus_Zul_Zorander = malloc(sizeof(personnage_t));
  init_hero(Zeddicus_Zul_Zorander,2,11,3,4,2,"Zeddicus Zul'Zorander","🔮",pt_m,mage_noir);


  kombat(marvin, Zeddicus_Zul_Zorander,pt_m);

  free(pt_m);
  pt_m = NULL;
  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);

  return 0;

}

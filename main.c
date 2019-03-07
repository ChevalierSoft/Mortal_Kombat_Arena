#include<stdlib.h>
#include<stdio.h>
#include "fonctions.h"
#include "personnage.h"
#include "liste_ptr.h"


#define N 10

int main(int argc, char const *argv[]) {
  printf(RED"\n++++++++++++++++++++ M K Arena ++++++++++++++++++++\n"RESET);
  carte_t * pt_m= malloc(sizeof(carte_t));

  //on crée le plateau de jeu (#ez)

  init_liste();

  charger_partie(pt_m);

  //on crée un mage de chiansse ici (c'est zéro mais, mais.)
  personnage_t * marvin = malloc(sizeof(personnage_t)); // creer une structure marvin qui est un mage
  //_mage, _force,  _PV,_PV_MAX, _px, _py,  _pm,  _nom, *_pp, _nb_att
  init_hero(marvin,20,1,420,1,2,1,"marvin","🧙‍",1,pt_m,mage_blanc); // on initit la structure marvin avec ses stats
  //un deuxieme
  personnage_t * Zeddicus_Zul_Zorander = malloc(sizeof(personnage_t));
  init_hero(Zeddicus_Zul_Zorander,25,1,350,3,4,2,"Zeddicus Zul'Zorander","🧞‍",1,pt_m,mage_noir);

  kombat(marvin, Zeddicus_Zul_Zorander,pt_m);
  detruire_personnage(&marvin);
  detruire_personnage(&Zeddicus_Zul_Zorander);
  map_detruire(&pt_m);
  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);

  return 0;

}

#include "fonctions.h"
#include "personnage.h"


#define N 10

int main(int argc, char const *argv[]) {
  printf(RED"\n++++++++++++++++++++ M K Arena ++++++++++++++++++++\n"RESET);
  carellage_t map1[N][N];
  //on crée le plateau de jeu (#ez)
  init_map_f(map1);
  afficher_map(map1);

  //on crée un mage de chiansse ici (c'est zéro mais, mais.)
  mage_t * marvin = malloc(sizeof(mage_t)); // creer une structure marvin qui est un mage
  init_mage(marvin,1,1,1,2,1,"marvin","🔥",map1); // on initit la structure marvin avec les stats précédentes
  info_mage(marvin);
  //un deuxieme
  mage_t * Zeddicus_Zul_Zorander = malloc(sizeof(mage_t));
  init_mage(Zeddicus_Zul_Zorander,2,2,3,4,2,"Zeddicus Zul'Zorander","🔮",map1);
  info_mage(Zeddicus_Zul_Zorander);


  afficher_map(map1);

  kombat(marvin, Zeddicus_Zul_Zorander);



  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);
  return 0;
}

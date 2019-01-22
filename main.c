#include "fonctions.h"
#include "personnage.h"

#define N 10

int main(int argc, char const *argv[]) {
  printf("\n+++++++++++++++ M K Arena +++++++++++++++\n");
  carellage_t map1[N][N];
  //on crée un mage de chiansse ici (c'est zéro mais, mais.)
  mage_t * marvin = malloc(sizeof(mage_t)); // creer une structure marvin qui est un mage
  int a = 1, b = 1, c = 1, d = 1;// force, pv, px, py
  char *e = "marvin";//nom
  char *f = "😁";
  init_mage(marvin,a,b,c,d,e,f); // on initit la structure marvin avec les stats précédentes
  afficher_mage(marvin);

  //on crée le plateau de jeu (#ez)
  init_map_f(map1);
  afficher_map(map1);

  printf("\n+++++++++++++++++++++++++++++++++++++++++++++++\n");
  return 0;
}

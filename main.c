#include "fonctions.h"
#include "structure.h"

int main(int argc, char const *argv[]) {
  mage_t * marvin = malloc(sizeof(mage_t)); // creer une structure marvin qui est un mage
  int a = 1, b = 1, c = 1, d = 1;// force, pv, px, py
  char *e = "marvin";//nom
  init_mage(marvin,a,b,c,d,e); // on initit la structure marvin avec les stats précédentes
  printf("\npv 1 :%d\n", marvin->pv);
  afficher_mage(marvin);


  printf("ça marche\n");
  test_pull();
<<<<<<< HEAD

=======
printf("OMEGAPOG\n");
>>>>>>> 3f1a61a70bb58fef46546944dc601afcd5ee85ed
  return 0;
}

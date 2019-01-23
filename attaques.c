/*extern*/
#include "fonctions.h"
#include "personnage.h"

void boule_feux(mage_t *m){
  int range = 0;
  int cout = 1;
  int type = 1;

  if(m->pm > cout){
    m->pm = m->pm - cout;
  }
  else {
    printf("\nmana insuffisant\n");
  }
}

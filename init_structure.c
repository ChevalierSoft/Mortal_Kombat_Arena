#include "fonctions.h"
#include "structure.h"

void init_mage(mage_t *m, int a, int  b, int c, int d, char * e){
  m->nom = malloc(sizeof(char)*strlen(e));
  m->force = a;
  m->pv = b;
  m->px = c;
  m->py = d;
  strcpy(m->nom,e);
}

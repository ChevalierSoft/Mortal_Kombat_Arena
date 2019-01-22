#include "fonctions.h"
#include "personnage.h"

void init_mage(mage_t *m, int a, int  b, int c, int d, char * e,char * f){
  m->nom = malloc(sizeof(char)*strlen(e));
   m->pp = malloc(sizeof(char)*strlen(f));
  m->force = a;
  m->pv = b;
  m->px = c;
  m->py = d;
  strcpy(m->nom,e);
  strcpy(m->pp,f);
}

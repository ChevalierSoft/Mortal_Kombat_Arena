#include "fonctions.h"
#include "personnage.h"

void placement(mage_t *m,carellage_t n[N][N]){
  n[m->px][m->py].personnage = m;
}

void init_mage(mage_t *m, int a, int  b, int c, int d, int g, char * e,char * f,carellage_t n[N][N]){
  m->nom = malloc(sizeof(char)*strlen(e));
  m->pp = malloc(sizeof(char)*strlen(f));
  m->force = a;
  m->pv = b;
  m->px = c;
  m->py = d;
  m->pm = g;
  strcpy(m->nom,e);
  strcpy(m->pp,f);
  placement(m,n);

}

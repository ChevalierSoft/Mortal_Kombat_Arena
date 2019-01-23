#ifndef H_M
#define H_M

#include "fonctions.h"
#include "personnage.h"

#define N 10

typedef struct carellage_s{
  int land;
  mage_t * personnage;
}carellage_t;

void init_map(carellage_t map[N][N]);
void afficher_map();
void init_map_f(carellage_t map[N][N]);

#endif

#ifndef H_M
#define H_M

#include "fonctions.h"
#include "personnage.h"

#define N 10

typedef struct dalle_s{
  int land;
  personnage_t * personnage;
}dalle_t;

typedef struct carte_s{
  int nb_dalles;
  dalle_t * map[N][N];
}carte_t;

void init_map(carte_t * pt_m);
void afficher_map(carte_t * pt_m);
void charger_partie(carte_t * pt_m);
void map_detruire(carte_t ** pt_m);

#endif

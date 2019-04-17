#ifndef H_M
#define H_M

#include "fonctions.h"
#include "personnage.h"

#define N 10

/**
* \struct dalle_s
* \brief Structure représentant une dalle
*/

typedef struct dalle_s{
  int land;
  personnage_t * personnage;
}dalle_t;

/**
* \struct carte_s
* \brief Structure de la carte
*/
typedef struct carte_s{
  int nb_dalles_x;
  int nb_dalles_y;
  dalle_t * map[N][N]; /* changer en double pointeur map */
}carte_t;

void init_map(carte_t * pt_m);
void afficher_map(carte_t * pt_m);
void charger_partie(carte_t * pt_m);
void map_detruire(carte_t ** pt_m);

#endif

#ifndef H_F
#define H_F

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "personnage.h"
#include "couleur.h"
#include "map.h"

void boule_de_feu(mage_t *m,carellage_t n[N][N]);
void init_mage(mage_t * _mage, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N]);
void afficher_mage(mage_t * marvin);

void pas_fini(void);
void menu_choix(mage_t * m, carellage_t map[N][N]);
void info_mage(mage_t *m);
void kombat(mage_t * m1, mage_t * m2,carellage_t map1[N][N]);

#endif

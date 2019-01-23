#ifndef H_F
#define H_F

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "personnage.h"
#include "couleur.h"
#include "map.h"



void boule_feux(mage_t *m);
void init_mage(mage_t *m, int a, int  b, int c, int d, int g, char * e, char *f,carellage_t n[N][N]);
void afficher_mage(mage_t * marvin);

void pas_fini(void);
void menu_choix(mage_t * m);
void info_mage(mage_t *m);
void kombat(mage_t * m1, mage_t * m2);

#endif

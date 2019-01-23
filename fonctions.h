#ifndef H_F
#define H_F

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "personnage.h"
#include "couleur.h"
#include "map.h"


void charge_test(void);
void  test_pull(void);
void init_mage(mage_t *m, int a, int  b, int c, int d, char * e, char *f);
void afficher_mage(mage_t * marvin);

#endif

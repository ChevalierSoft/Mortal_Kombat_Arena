#ifndef H_F
#define H_F

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h> 
#include "personnage.h"
#include "couleur.h"
#include "map.h"

void boule_de_feu(personnage_t *_personnage,carte_t * pt_m);
void init_hero(personnage_t * _personnage, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carte_t * pt_m,int classe);
void afficher_mage(personnage_t * marvin);
void soin(personnage_t *_personnage,carte_t * pt_m);

void pas_fini(void);
void menu_choix(personnage_t * _personnage, carte_t * pt_m);
void info_mage(personnage_t *_personnage);
void kombat(personnage_t * _personnage1, personnage_t * _personnage2,carte_t * pt_m);
int deplacement(personnage_t *_personnage, carte_t * pt_m);
int range_detection(personnage_t *_personnage,int range,int x,int y);

#endif

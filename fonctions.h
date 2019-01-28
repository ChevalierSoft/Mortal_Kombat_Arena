#ifndef H_F
#define H_F

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "personnage.h"
#include "couleur.h"
#include "map.h"

void boule_de_feu(personnage_t *_personnage,carellage_t map[N][N]);
void init_hero(personnage_t * _personnage, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N],int classe);
void afficher_mage(personnage_t * marvin);
void soin(personnage_t *_personnage,carellage_t n[N][N]);

void pas_fini(void);
void menu_choix(personnage_t * _personnage, carellage_t map[N][N]);
void info_mage(personnage_t *_personnage);
void kombat(personnage_t * _personnage1, personnage_t * _personnage2,carellage_t map[N][N]);

#endif

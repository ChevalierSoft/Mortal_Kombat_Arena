#ifndef H_F
#define H_F

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdarg.h>
#include<string.h>
#include "personnage.h"
#include "couleur.h"
#include "map.h"
#include "menu.h"


void init_hero(personnage_t * _personnage, int _force, int  _pv, int _pv_max, int _px, int _py, int _pm, char * _nom, char * _pp, int _nb_att, carte_t * pt_m,int classe);
void afficher_mage(personnage_t * marvin);
void soin(personnage_t *_personnage,carte_t * pt_m);
void soin_cb(void *_personnage, void * pt_m);
void cure(personnage_t *_personnage, carte_t * pt_m);
void cure_cb(void *_personnage, void * pt_m);
void boule_de_feu(personnage_t *_personnage,carte_t * pt_m);
void boule_de_feu_cb(void *_personnage,void * pt_m);
void summon(personnage_t *_personnage, carte_t * pt_m);
void summon_cb(void *_personnage, void * pt_m);
void sheep(personnage_t *_personnage, carte_t * pt_m);
void sheep_cb(void *_personnage, void * pt_m);
/*
void pas_fini(void);
void menu_choix(personnage_t * _personnage, carte_t * pt_m);
void info_mage(personnage_t *_personnage);
void kombat(personnage_t * _personnage1, personnage_t * _personnage2,carte_t * pt_m);
*/
void deplacement(personnage_t *_personnage, carte_t * pt_m);
int range_detection(personnage_t *_personnage,int range,int x,int y);
void toxicite(personnage_t * personnage,carte_t * pt_m);
void toxicite_cb(void * personnage,void * pt_m);
void tourbilol(personnage_t * personnage,carte_t * pt_m);
void tourbilol_cb(void * personnage,void * pt_m);
void shield(personnage_t * personnage,carte_t * pt_m);
void shield_cb(void * personnage,void * pt_m);
void fait_ton_greu(personnage_t * personnage,carte_t * pt_m);
void fait_ton_greu_cb(void * personnage,void * pt_m);
void detruire_personnage(personnage_t **);
void detruire_spell(personnage_t ** _personnage);
void detruire_liste(void);

#endif

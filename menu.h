#ifndef H_MENU
#define H_MENU

#include "fonctions.h"

void menu_start(void);
int  menu_main(void);
void pas_fini(void);
void menu_choix(personnage_t * _personnage, carte_t * pt_m);
void info_mage(personnage_t *_personnage);
void kombat(carte_t * pt_m);
void backdash( personnage_t * ex);

#endif

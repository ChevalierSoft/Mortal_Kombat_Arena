#ifndef H_MENU
#define H_MENU

#include "fonctions.h"
#include "reseau.h"

void menu_start(void);
int  menu_main(void);
void gg(char * nom);
void pas_fini(void);
action_t * menu_choix(personnage_t * sasuke, carte_t * pt_m, int web);
void info_personnage(personnage_t *_personnage);
void kombat(carte_t * pt_m);
void backdash( personnage_t * ex);
int get_hp_team(int n);

#endif

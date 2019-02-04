#ifndef H_S
#define H_S

#include "fonctions.h"

typedef enum {mage_blanc,mage_noir,chevalier,necromencien,tacticien}heros_classes;

typedef struct personnage{
  char * nom;
  int px;
  int py;
  int pv;
  int pm;
  int force;
  char * pp;
  int classe;

	int est_empoisone;
	int est_mort;
	int est_enfeu;
	int intel;
	int chance;		/* pour les critiques*/

}personnage_t;




#endif

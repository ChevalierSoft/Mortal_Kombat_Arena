#ifndef H_S
#define H_S

#include "fonctions.h"

typedef enum {mage_blanc, mage_noir, chevalier, necromencien, tacticien} heros_classes;

/*typedef struct personnage_s personnage_t;*/

typedef struct personnage_s{
  char * nom;
  int px;
  int py;
  int pv;
  int pm;
  int force;
  char * pp;
  int classe;

  char * f1_nom;
  char * f2_nom;
  char * f3_nom;
  char * f4_nom;
  void (*f1)(void *_personnage, void * pt_m);
  void (*f2)(void *_personnage, void * pt_m);
  void (*f3)(void *_personnage, void * pt_m);
  void (*f4)(void *_personnage, void * pt_m);

  int est_shield;
	int est_mort;
  int est_empoisone;
	int est_enfeu;
	int intel;
	int chance;		/* pour les critiques*/

}personnage_t;




#endif

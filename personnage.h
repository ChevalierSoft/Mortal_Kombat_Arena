#ifndef H_S
#define H_S

#include "fonctions.h"

typedef enum {mage_blanc, mage_noir, chevalier, necromancien, tacticien, ninja} heros_classes;

/*typedef struct personnage_s personnage_t;*/

typedef void (*attaque_t)(void *);

typedef struct personnage_s{
  char * nom;
  int px;
  int py;
  int pv;
  /*pv_max*/
  int pm;
  int force;
  char * pp;
  int classe;

  int nb_attaques;
  char ** nom_spell;
  void (**tab_spell)(void *, void *);

  int est_shield;
	int est_mort;
  int est_empoisone;
	int est_enfeu;
	int intel;
	int chance;		/* pour les critiques*/

}personnage_t;




#endif

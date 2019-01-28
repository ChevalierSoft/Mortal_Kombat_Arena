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


}personnage_t;




#endif

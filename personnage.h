#ifndef H_S
#define H_S

typedef enum {mage_blanc, mage_noir, chevalier, necromancien, tacticien, ninja, shrek, sac, delimiteur} heros_classes;

/*typedef struct personnage_s personnage_t;*/

typedef void (*attaque_t)(void *, void *, int, int);

typedef struct personnage_s{
  char * nom;
  char * pp;

  int id;
  int classe;

  int px;
  int py;

  int pv;
  int pv_max;
  int pm;
  int intel;
  int force;
  int chance;   /* pour les critiques*/

  int nb_spell;
  char ** nom_spell;
  void (**tab_spell)(void *, void *, int, int);

  int est_sheep;
  int est_shield;
	int est_mort;
  int est_empoisone;
	int est_enfeu;

}personnage_t;




#endif

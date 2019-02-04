#include "fonctions.h"
#include "personnage.h"

void placement(personnage_t *_personnage,carte_t * pt_m){
  pt_m->map[_personnage->px][_personnage->py]->personnage = _personnage;

}

void init_mage_blanc(personnage_t * _mage_blanc ){
  _mage_blanc->f1_nom = malloc(sizeof(char)*strlen("boule de feu"));
  strcmp(_mage_blanc->f1_nom, "boule de feu");
  _mage_blanc->f1 = &soin_cb;
}

void init_mage_noir(personnage_t * _mage_noir ){
  _mage_noir->f1 = &boule_de_feu_cb;
}

void init_chevalier(personnage_t * _chevalier ){

}

void init_necromencien(personnage_t * _necromencien ){

}

void init_tacticien(personnage_t * _tacticien ){

}

void init_hero(personnage_t * _personnage, int _force, int _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carte_t * pt_m,int _classe){

  _personnage->nom = malloc(sizeof(char)*strlen(_nom));
  _personnage->pp = malloc(sizeof(char)*strlen(_pp));
  strcpy(_personnage->nom, _nom);
  strcpy(_personnage->pp, _pp);

  _personnage->force = _force;
  _personnage->pv = _PV;
  _personnage->px = _px;
  _personnage->py = _py;
  _personnage->pm = _pm;
  _personnage->classe = _classe;

  _personnage->est_empoisone=0;
	_personnage->est_mort=0;
	_personnage->est_enfeu=0;
	_personnage->intel=0;
	_personnage->chance=0;

  placement(_personnage, pt_m);

  switch(_classe){
    case mage_blanc:init_mage_blanc( _personnage);break;
    case mage_noir:init_mage_noir(_personnage);break;
    case chevalier:init_chevalier(_personnage);break;
    case necromencien:init_necromencien(_personnage);break;
    case tacticien:init_tacticien(_personnage);break;
    default:printf("ERROR !!!!!!!!!!!");break;
  }
}

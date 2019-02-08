#include "fonctions.h"
#include "personnage.h"

void placement(personnage_t *_personnage,carte_t * pt_m){
  pt_m->map[_personnage->px][_personnage->py]->personnage = _personnage;
}

void init_spell(personnage_t * p, int nb_spell, ...){
  int i=0;
  va_list liste;

  va_start(liste, nb_spell);

  p->nom_spell = malloc(sizeof(char *) * p->nb_spell);
  p->tab_spell = malloc(sizeof(attaque_t)*p->nb_spell);

  for(; i < p->nb_spell ; i++){
    char * arg_nom = va_arg(liste,char *);
    p->nom_spell[i] = malloc(sizeof(char)*strlen(arg_nom));
    strcpy(p->nom_spell[i], arg_nom);

    void *arg_f = va_arg(liste,void *);
    p->tab_spell[i] = malloc(sizeof(attaque_t));
    p->tab_spell[i] = arg_f;
  }

}

void init_mage_blanc(personnage_t * _mage_blanc ){

  _mage_blanc->nb_spell = 2;

  init_spell(_mage_blanc,_mage_blanc->nb_spell,"Soin", &soin_cb, "Cure", cure_cb );

}

void init_mage_noir(personnage_t * _mage_noir ){

  _mage_noir->nb_spell = 2;

  init_spell(_mage_noir,_mage_noir->nb_spell,"Boule de feu", &boule_de_feu_cb, "Toxicite", &toxicite_cb );

}

void init_chevalier(personnage_t * _chevalier ){

}

void init_necromancien(personnage_t * _necromencien ){

}

void init_tacticien(personnage_t * _tacticien ){

}

void init_ninja(personnage_t * _ninja ){

}

void init_hero(personnage_t * _personnage, int _force, int _PV, int _px, int _py, int _pm, char * _nom, char * _pp, int _nb_att, carte_t * pt_m,int _classe){

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

  _personnage->est_shield=0;
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
    case necromancien:init_necromancien(_personnage);break;
    case tacticien:init_tacticien(_personnage);break;
    case ninja:init_ninja(_personnage);break;
    default:printf("ERROR !!!!!!!!!!!");break;
  }
}

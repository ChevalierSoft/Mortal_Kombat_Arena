#include "fonctions.h"
#include "personnage.h"
#include "liste_ptr.h"


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
    p->nom_spell[i] = malloc(sizeof(char)*strlen(arg_nom)+1);
    strcpy(p->nom_spell[i], arg_nom);

    void *arg_f = va_arg(liste,void *);
    p->tab_spell[i] =(void*) malloc(sizeof(attaque_t));
    p->tab_spell[i] = arg_f;
  }

}

void init_mage_blanc(personnage_t * _mage_blanc ){

  _mage_blanc->nb_spell = 3;

  init_spell(_mage_blanc,_mage_blanc->nb_spell,"Soin", &soin_cb, "Cure", cure_cb, "Armure", &shield_cb );

}

void init_mage_noir(personnage_t * _mage_noir ){

  _mage_noir->nb_spell = 5;

  init_spell(_mage_noir,_mage_noir->nb_spell,"Boule de feu", &boule_de_feu_cb, "Toxicite", &toxicite_cb, "Fait ton greu", &fait_ton_greu_cb,"summon",&summon_cb,"db_evolution",&sheep_cb );

}

void init_chevalier(personnage_t * _chevalier ){

}

void init_necromancien(personnage_t * _necromencien ){

}

void init_tacticien(personnage_t * _tacticien ){

}

void init_ninja(personnage_t * _ninja ){

}

void init_sac(personnage_t * _sac ){

}

void init_hero(personnage_t * _personnage, int _force, int _pv, int _pv_max, int _px, int _py, int _pm, char * _nom, char * _pp, int _nb_att, carte_t * pt_m,int _classe){

  _personnage->nom = malloc(sizeof(char)*strlen(_nom)+1);
  _personnage->pp = malloc(sizeof(char)*strlen(_pp)+1);
  strcpy(_personnage->nom, _nom);
  strcpy(_personnage->pp, _pp);
  _personnage->classe = _classe;


  _personnage->px = _px;
  _personnage->py = _py;

  _personnage->pv = _pv;
  _personnage->pv_max = _pv_max;
  _personnage->pm = _pm;
  _personnage->intel=0;
  _personnage->force = _force;

  _personnage->est_shield=0;
  _personnage->est_empoisone=0;
	_personnage->est_mort=0;
	_personnage->est_enfeu=0;

	_personnage->chance=0;

  placement(_personnage, pt_m);

  //AJOUT DU PERSONNAGE DANS LA LISTE
  printf("Avant liste vide\n");
  if(liste_vide()){
    printf("Avant en tete\n");

    en_tete();
    printf("Avant ajout droit\n");
		ajout_droit(_personnage);
	}
	else{
    printf("Avant en queue\n");
		en_queue();
    printf("avant ajout droit\n");
		ajout_droit(_personnage);
	}
  //------------------------------------------

  switch(_classe){
    case mage_blanc:init_mage_blanc( _personnage);break;
    case mage_noir:init_mage_noir(_personnage);break;
    case chevalier:init_chevalier(_personnage);break;
    case necromancien:init_necromancien(_personnage);break;
    case tacticien:init_tacticien(_personnage);break;
    case ninja:init_ninja(_personnage);break;
    case sac:init_sac(_personnage);break;
    default:printf("ERROR !!!!!!!!!!!");break;
  }

}

void detruire_personnage(personnage_t** _personnage){
  //detruire_spell(_personnage); <- probleme free
  personnage_t * pcourant;
  en_tete();
  valeur_elt(&pcourant);
  while(pcourant != &_personnage){
    suivant();
  }
  oter_elt();
  free((*_personnage)->nom);
  free((*_personnage)->pp);
  (*_personnage)->pp = NULL;
  (*_personnage)->nom = NULL;
  free((*_personnage));
}

void detruire_spell(personnage_t ** _personnage){
  int i;
  /*printf("\nnb de spells : %d\n",(*_personnage)->nb_spell );*/
  for(i=0;i<=(*_personnage)->nb_spell-1;i++){
    /*printf("\nnb de i : %d\n",i);*/
    free((*_personnage)->nom_spell[i]);
    /*printf("\ntab du spell : %p\n",(*_personnage)->tab_spell[i]);*/
    free((*_personnage)->tab_spell+i*sizeof(attaque_t)*(*_personnage)->nb_spell);/*cette ligne pause probleme*/
    (*_personnage)->nom_spell[i] = NULL;
    /*printf("\ntab du spell null : %p\n",(*_personnage)->tab_spell[i]);*/
    (*_personnage)->tab_spell[i] = ((void*)0);
  }
  free((*_personnage)->nom_spell);
  free((*_personnage)->tab_spell);
//  (*_personnage)->nom_spell = NULL;
//  (*_personnage)->tab_spell = NULL;

}

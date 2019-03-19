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
    //il n'y avait pas besoin d'allouer de la memoire pour les fonctions
    //p->tab_spell[i] =(void*) malloc(sizeof(attaque_t));
    p->tab_spell[i] = arg_f;
  }

}

void init_mage_blanc(personnage_t * _mage_blanc ){
  char *pp = "🧙‍";
  _mage_blanc->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(_mage_blanc->pp, pp);

  _mage_blanc->nb_spell = 3; //3
  init_spell(_mage_blanc,_mage_blanc->nb_spell,"Soin", &soin_cb, "Cure", cure_cb, "Armure", &shield_cb );

}

void init_mage_noir(personnage_t * _mage_noir ){
  
  char *pp = "🧞‍";
  _mage_noir->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(_mage_noir->pp, pp);
  
  _mage_noir->nb_spell = 5; //5
  init_spell(_mage_noir,_mage_noir->nb_spell,"Boule de feu", &boule_de_feu_cb, "Toxicite", &toxicite_cb, "Fait ton greu", &fait_ton_greu_cb,"summon",&summon_cb,"sheep",&sheep_cb );

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
  char *pp = "💼";
  _sac->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(_sac->pp, pp);

  _sac->nb_spell = 0;

}

void init_delimiteur(personnage_t * del ){
  char *pp = "👽";
  del->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(del->pp, pp);

  del->nb_spell = 0;
}

void init_hero(personnage_t * _personnage, int _force, int _pv, int _pv_max, int _px, int _py, int _pm, char * _nom, carte_t * pt_m,int _classe){

  _personnage->nom = malloc(sizeof(char)*strlen(_nom));
  strcpy(_personnage->nom, _nom);
  
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

  if (_personnage->classe != delimiteur){
    placement(_personnage, pt_m);
  }

  //AJOUT DU PERSONNAGE DANS LA LISTE

  if(liste_vide()){
    en_tete();
    //printf("ajout droit\n");
		ajout_droit(_personnage);
	}
	else{
    //printf("Avant en queue\n");
		en_queue();
    //printf("avant ajout droit\n");
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
    case delimiteur:init_delimiteur(_personnage);break;
    default:printf("Erreur de classe");init_sac(_personnage);break;
  }

}

void detruire_liste(){

  en_tete();
  while(!liste_vide() && !hors_liste()){

    oter_elt();
    suivant();
    en_tete();

  }

}

void detruire_personnage(personnage_t** p){

  free((*p)->nom);
  free((*p)->pp);
  (*p)->pp = NULL;
  (*p)->nom = NULL;
  free((*p));
}

void detruire_spell(personnage_t ** personnage){
  int i;
  /*printf("\nnb de spells : %d\n",(*personnage)->nb_spell );*/
  for(i=0;i<=(*personnage)->nb_spell-1;i++){   
    free((*personnage)->nom_spell[i]);
    (*personnage)->nom_spell[i] = NULL;
    (*personnage)->tab_spell[i] = ((void*)0);
  }
  free((*personnage)->nom_spell);
  free((*personnage)->tab_spell);
//  (*personnage)->nom_spell = NULL;
//  (*personnage)->tab_spell = NULL;

}

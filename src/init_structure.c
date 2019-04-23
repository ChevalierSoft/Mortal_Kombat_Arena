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

  _mage_blanc->pv = 310;
  _mage_blanc->pv_max = 310;
  _mage_blanc->pm = 200;
  _mage_blanc->intel=0;
  _mage_blanc->force = 11;
  _mage_blanc->chance=0;

}

void init_mage_noir(personnage_t * mage_noir ){

  char *pp = "🧞‍";
  mage_noir->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(mage_noir->pp, pp);

  mage_noir->nb_spell = 2; //5
  init_spell(mage_noir,mage_noir->nb_spell,"Boule de feu", &boule_de_feu_cb, "Toxicite", &toxicite_cb);

  mage_noir->pv = 299;
  mage_noir->pv_max = 299;
  mage_noir->pm = 199;
  mage_noir->intel = 0;
  mage_noir->force = 1;
  mage_noir->chance=0;

}

void init_chevalier(personnage_t * chevalier ){
  char *pp = "🌅‍";
  chevalier->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(chevalier->pp, pp);

  chevalier->nb_spell = 3;
  init_spell(chevalier,chevalier->nb_spell, "Fait ton greu", &fait_ton_greu_cb, "Tourbilol", &tourbilol_cb,"jet de sable",&jet_de_sable_cb);

  chevalier->pv = 700;
  chevalier->pv_max = 700;
  chevalier->pm = 20;
  chevalier->intel = 1;
  chevalier->force = 70;
  chevalier->chance = 2;

}

void init_necromancien(personnage_t * necromencien ){
	char *pp = "🤬";
  necromencien->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(necromencien->pp, pp);

  necromencien->nb_spell = 2;
  init_spell(necromencien,necromencien->nb_spell,"summon",&summon_cb,"sheep",&sheep_cb);
  
  necromencien->pv = 330;
  necromencien->pv_max = 330;
  necromencien->pm = 320;
  necromencien->intel = 30;
  necromencien->force = 5;
  necromencien->chance = 0;
}

void init_tacticien(personnage_t * tacticien ){
	char *pp = "👩‍🔧";
  tacticien->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(tacticien->pp, pp);

  tacticien->nb_spell = 0;

  tacticien->pv = 350;
  tacticien->pv_max = 350;
  tacticien->pm = 210;
  tacticien->intel= 25;
  tacticien->force = 30;
  tacticien->chance = 0;
}

void init_ninja(personnage_t * ninja ){

	char *pp = "🐱‍👤";
  ninja->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(ninja->pp, pp);

  ninja->nb_spell = 0;

  ninja->pv = 500;
  ninja->pv_max = 500;
  ninja->pm = 20;
  ninja->intel = 4;
  ninja->force = 80;
  ninja->chance = 5;
}

void init_sac(personnage_t * sac ){
  char *pp = "💼";
  sac->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(sac->pp, pp);

  sac->nb_spell = 1;
  init_spell(sac,sac->nb_spell, "arakiri",&arakiri_cb);

  sac->pv = 1;
  sac->pv_max = 300;
  sac->pm = 3;
  sac->intel = 10;
  sac->force = 20;
  sac->chance = 20;

}

void init_delimiteur(personnage_t * del ){
  char *pp = "👽";
  del->pp = malloc(sizeof(char)*strlen(pp));
  strcpy(del->pp, pp);

  del->nb_spell = 0;

  del->pv = 1;
  del->pv_max = 1;
  del->pm = 0;
  del->intel= 9999;
  del->force = 0;
  del->chance = 42;
}

void init_hero(personnage_t * _personnage, int _id, int _px, int _py, char * _nom, carte_t * pt_m, int _classe){

  _personnage->nom = malloc(sizeof(char)*strlen(_nom));
  strcpy(_personnage->nom, _nom);
  _personnage->id = _id;
  _personnage->classe = _classe;

  _personnage->px = _px;
  _personnage->py = _py;

  _personnage->est_shield=0;
  _personnage->est_sheep=0;
  _personnage->est_empoisone=0;
	_personnage->est_mort=0;
	_personnage->est_enfeu=0;
  _personnage->est_aveugle=0; //test

	//le délimiteur est omnitient
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

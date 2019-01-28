#include "fonctions.h"
#include "personnage.h"

void placement(personnage_t *_personnage,carellage_t map[N][N]){
  map[_personnage->px][_personnage->py].personnage = _personnage;
}

void init_mage_blanc(personnage_t * _mage_blanc, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N],int _classe ){
  _mage_blanc->nom = malloc(sizeof(char)*strlen(_nom));
  _mage_blanc->pp = malloc(sizeof(char)*strlen(_pp));
  _mage_blanc->force = _force;
  _mage_blanc->pv = _PV;
  _mage_blanc->px = _px;
  _mage_blanc->py = _py;
  _mage_blanc->pm = _pm;
  strcpy(_mage_blanc->nom, _nom);
  strcpy(_mage_blanc->pp, _pp);
  placement(_mage_blanc, map);
  _mage_blanc->classe = _classe;
}

void init_mage_noir(personnage_t * _mage_noir, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N],int _classe ){
  _mage_noir->nom = malloc(sizeof(char)*strlen(_nom));
  _mage_noir->pp = malloc(sizeof(char)*strlen(_pp));
  _mage_noir->force = _force;
  _mage_noir->pv = _PV;
  _mage_noir->px = _px;
  _mage_noir->py = _py;
  _mage_noir->pm = _pm;
  strcpy(_mage_noir->nom, _nom);
  strcpy(_mage_noir->pp, _pp);
  placement(_mage_noir, map);
  _mage_noir->classe = _classe;
}

void init_chevalier(personnage_t * _chevalier, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N],int _classe ){
  _chevalier->nom = malloc(sizeof(char)*strlen(_nom));
  _chevalier->pp = malloc(sizeof(char)*strlen(_pp));
  _chevalier->force = _force;
  _chevalier->pv = _PV;
  _chevalier->px = _px;
  _chevalier->py = _py;
  _chevalier->pm = _pm;
  strcpy(_chevalier->nom, _nom);
  strcpy(_chevalier->pp, _pp);
  placement(_chevalier, map);
  _chevalier->classe = _classe;
}

void init_necromencien(personnage_t * _necromencien, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N],int _classe ){
  _necromencien->nom = malloc(sizeof(char)*strlen(_nom));
  _necromencien->pp = malloc(sizeof(char)*strlen(_pp));
  _necromencien->force = _force;
  _necromencien->pv = _PV;
  _necromencien->px = _px;
  _necromencien->py = _py;
  _necromencien->pm = _pm;
  strcpy(_necromencien->nom, _nom);
  strcpy(_necromencien->pp, _pp);
  placement(_necromencien, map);
  _necromencien->classe = _classe;
}

void init_tacticien(personnage_t * _tacticien, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N],int _classe ){
  _tacticien->nom = malloc(sizeof(char)*strlen(_nom));
  _tacticien->pp = malloc(sizeof(char)*strlen(_pp));
  _tacticien->force = _force;
  _tacticien->pv = _PV;
  _tacticien->px = _px;
  _tacticien->py = _py;
  _tacticien->pm = _pm;
  strcpy(_tacticien->nom, _nom);
  strcpy(_tacticien->pp, _pp);
  placement(_tacticien, map);
  _tacticien->classe = _classe;
}
void init_hero(personnage_t * _personnage, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N],int _classe){
    switch(_classe){
      case mage_blanc:init_mage_blanc( _personnage, _force, _PV, _px, _py, _pm, _nom, _pp, map,_classe);break;
      case mage_noir:init_mage_noir(_personnage, _force, _PV, _px, _py, _pm, _nom, _pp, map,_classe);break;
      case chevalier:init_chevalier(_personnage, _force, _PV, _px, _py, _pm, _nom, _pp, map,_classe);break;
      case necromencien:init_necromencien(_personnage, _force, _PV, _px, _py, _pm, _nom, _pp, map,_classe);break;
      case tacticien:init_tacticien(_personnage, _force, _PV, _px, _py, _pm, _nom, _pp, map,_classe);break;
      default:printf("ERROR !!!!!!!!!!!");break;
    }
}

#include "fonctions.h"
#include "personnage.h"

void placement(mage_t *m,carellage_t n[N][N]){
  n[m->px][m->py].personnage = m;
}

void init_mage(mage_t * _mage, int _force, int  _PV, int _px, int _py, int _pm, char * _nom, char * _pp, carellage_t map[N][N]){
  _mage->nom = malloc(sizeof(char)*strlen(_nom));
  _mage->pp = malloc(sizeof(char)*strlen(_pp));
  _mage->force = _force;
  _mage->pv = _PV;
  _mage->px = _px;
  _mage->py = _py;
  _mage->pm = _pm;
  strcpy(_mage->nom, _nom);
  strcpy(_mage->pp, _pp);
  placement(_mage, map);

}

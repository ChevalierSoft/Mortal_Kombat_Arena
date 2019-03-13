 #include<stdlib.h>
#include<stdio.h>
#include "fonctions.h"
#include "personnage.h"
#include "liste_ptr.h"

#define N 10

int main(int argc, char const *argv[]) {
  printf(RED"\n++++++++++++++++++++ M K Arena ++++++++++++++++++++\n"RESET);
  //on crée le plateau de jeu (#ez)
  carte_t * pt_m= malloc(sizeof(carte_t));
  //on crée une liste de perso
  init_liste();
  //on charge la map
  charger_partie(pt_m);
  //on crée un mage de chiansse ici (c'est zéro mais, mais.)
  personnage_t * marvin = malloc(sizeof(personnage_t)); // creer une structure marvin qui est un mage
  //        _nom, _force, _PV,_PV_MAX, _px, _py,  _pm,  *_nom, *_pp, _nb_att, classe
  init_hero(marvin,20,10,420,1,2,1,"marvin",pt_m,mage_blanc); // on initit la structure marvin avec ses stats

  //delimiteur
  personnage_t * del = malloc(sizeof(personnage_t));
  init_hero(del,0,1,1,-1,-1,1,"delimiteur",pt_m,delimiteur);
  
  //un deuxieme
  personnage_t * Zeddicus_Zul_Zorander = malloc(sizeof(personnage_t));
  init_hero(Zeddicus_Zul_Zorander,25,350,350,3,4,2,"Zeddicus Zul'Zorander",pt_m,mage_noir);
  
  //affiche les persos dans la liste
  afficher_liste();
  
  kombat(marvin, Zeddicus_Zul_Zorander,pt_m);
  
  //fonction pour enlever tous les persos de la liste
  detruire_liste();
  
  printf("free map\n");
  map_detruire(&pt_m);
  afficher_liste();
  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);

  return 0;

}

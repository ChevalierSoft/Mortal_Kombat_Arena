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
  /*--------------- team 1 ---------------*/
  //on crée un mage de chiansse ici (c'est zéro mais, mais.)
  personnage_t * marvin = malloc(sizeof(personnage_t)); // creer une structure marvin qui est un mage
  //        _nom, _px, _py, *_nom,  classe
  init_hero(marvin, 1, 2, "Marvin", pt_m,mage_blanc); // on initit la structure marvin avec ses stats

  //Solaire
  personnage_t * solaire = malloc(sizeof(personnage_t));
  init_hero(solaire, 7, 7, "Solaire", pt_m, chevalier);


  /*--------------delimiteur--------------*/
  personnage_t * del = malloc(sizeof(personnage_t));
  init_hero(del, -1,-1, "delimiteur", pt_m, delimiteur);

  /*--------------- team 2 ---------------*/
  personnage_t * Zeddicus_Zul_Zorander = malloc(sizeof(personnage_t));
  init_hero(Zeddicus_Zul_Zorander, 3, 4, "Zeddicus Zul'Zorander", pt_m, mage_noir);

  /*lancement de la partie*/
  kombat(pt_m);

  //fonction pour free tous les persos de la liste
  detruire_liste();

  printf("free map\n");
  map_detruire(&pt_m);
  afficher_liste();
  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);

  return 0;

}

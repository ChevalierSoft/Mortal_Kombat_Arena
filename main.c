#include "fonctions.h"






int main(int argc, char const *argv[]) {

  printf(RED"\n++++++++++++++++++++ M K Arena ++++++++++++++++++++\n"RESET);
  //on crée le plateau de jeu (#ez)
  carte_t * pt_m= malloc(sizeof(carte_t));
  //on crée une liste de perso
  init_liste();
  //on charge la map
  charger_partie(pt_m);
  //on charge les persos
  load_perso(pt_m);
  //lancement de la partie
  kombat(pt_m);

  /*en_tete();
  personnage_t * clodo;
  valeur_elt(&clodo);
  getXY(clodo, pt_m, tourbilol_cb);
  */

  //fonction pour free tous les persos de la liste
  detruire_liste();
  //free la map
  map_detruire(&pt_m);
  afficher_liste();
  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);

  return 0;

}

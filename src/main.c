#include "fonctions.h"






int main(int argc, char const *argv[]) {
  system("clear");
  printf(MAG"\n#######################################################################\n"RESET);
  int choix;
  // Squalala nous sommes parti
  menu_start();
  choix = menu_main();

  //on crée le plateau de jeu (#ez)
  carte_t * pt_m= malloc(sizeof(carte_t));
  //on crée une liste de perso
  init_liste();
  //on charge la map
  charger_partie(pt_m);
  //on charge les persos
  load_perso(pt_m);

  if (choix==1)  //lancement de la partie en split screen
    kombat(pt_m);
  else
    menu_online(pt_m); //lancement de la partie en reseau


  //fonction pour free tous les persos de la liste
  detruire_liste();
  //free la map
  map_detruire(&pt_m);
  //afficher_liste();


  printf(MAG"\n#######################################################################\n"RESET);

  return 0;

}

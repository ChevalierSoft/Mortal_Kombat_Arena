#include "fonctions.h"
#include "map.h"

#define N 10

/**
	* \file map.c
	* \brief Gestion de la carte
	* \author EL KANDOUSSI Adnan
	* \version	1.4
	* \date 17 avril 2019

*/

/**
* \fn void afficher_map(carte_t * pt_m)
* \brief Affichage en version terminal de l'environnement et des personnages sur la carte
* \param pt_m Pointeur sur la carte
* \return void  
*/

void afficher_map(carte_t * pt_m){
  int i,j,k;


  printf("Matrice terrain             Matrice pointeur perso\n");
  printf("                               0 1 2 3 4 5 6 7 8 9\n");
  for(j=0;j<N;j++){

    for(i=0;i<N;i++){

      switch ((pt_m)->map[i][j]->land) {
        case 0: printf(BLK"%d "RESET,(pt_m)->map[i][j]->land);break;
        case 1: printf(GRN"%d "RESET,(pt_m)->map[i][j]->land);break;
        case 2: printf(BLU"%d "RESET,(pt_m)->map[i][j]->land);break;
        case 3: printf(RED"%d "RESET,(pt_m)->map[i][j]->land);break;
        case 4: printf(MAG"%d "RESET,(pt_m)->map[i][j]->land);break;
        case 5: printf(YEL"%d "RESET,(pt_m)->map[i][j]->land);break;
        default: printf(WHT"%d"RESET,(pt_m)->map[i][j]->land);break;
      }
    }
    printf("          ");
    printf("%d",j);

    for(i=0;i<N;i++){
      //printf("%d",i);
      if((pt_m)->map[i][j]->personnage == NULL)
        printf(BLK"🔳"RESET);


      else
        printf("%s",(pt_m)->map[i][j]->personnage->pp);

    }

    printf("\n");
  }

}

/**
* \fn void init_map(carte_t * pt_m)
* \brief Initialise la carte à 1 pour les cases land et NULL pour les pointeurs personnage sur ces cases
* \param pt_m Pointeur sur la carte
* \return void  
*/

void init_map(carte_t * pt_m){ /* changer le malloc du à la transformation de map */
  int i,j;


  pt_m->nb_dalles_x = 20;
  pt_m->nb_dalles_y = 20;
  for(j=0;j<N;j++){
    for(i=0;i<N;i++){
      (pt_m)->map[i][j] = malloc(sizeof(dalle_t));
      (pt_m)->map[i][j]->land = 1;
      (pt_m)->map[i][j]->personnage=NULL;

    }
  }

}

/*void sauvegarder_partie(carte_t * pt_m){


}*/

/**
* \fn void charger_partie(carte_t * pt_m)
* \brief Charge un état de la carte depuis un fichier nommé "m_save.txt"
* \param pt_m Pointeur sur la carte
* \return void  
*/

void charger_partie(carte_t * pt_m){
  //Charge un etat de la map depuis un fichier
  init_map(pt_m);
  int x,y,l;

  FILE * sauvegarde;

  sauvegarde = fopen("save/m_save.txt","r");

  while(!feof(sauvegarde)){
    fscanf(sauvegarde,"%d %d %d",&x,&y,&l);
    pt_m->map[x][y]->land = l;
  }


}

/**
* \fn void map_detruire(carte_t ** pt_m)
* \brief Libère chaque dalle de la carte et le pointeur sur la carte 
* \param pt_m Pointeur sur la carte
* \return void  
*/


void map_detruire(carte_t ** pt_m){
  int i,j;

  for(j=0;j<N;j++){
    for(i=0;i<N;i++){
      free((*pt_m)->map[i][j]);
      (*pt_m)->map[i][j]=NULL;
    }
  }
  free((*pt_m));
  (*pt_m) = NULL;
}

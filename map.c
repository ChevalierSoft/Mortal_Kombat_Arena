#include "fonctions.h"
#include "map.h"

#define N 10


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



void init_map(carte_t * pt_m){ /* changer le malloc du à la transformation de map */
  int i,j;


  pt_m->nb_dalles_x = N;
  pt_m->nb_dalles_y = N;
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

void charger_partie(carte_t * pt_m){
  //Charge un etat de la map depuis un fichier
  init_map(pt_m);
  int x,y,l;

  FILE * sauvegarde;

  sauvegarde = fopen("save.txt","r");

  while(!feof(sauvegarde)){
    fscanf(sauvegarde,"%d %d %d",&x,&y,&l);
    pt_m->map[x][y]->land = l;
  }


}

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

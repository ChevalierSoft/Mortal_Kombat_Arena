#include "fonctions.h"
#include "map.h"

#define N 10


void afficher_map(carellage_t map[N][N]){
  int i,j;

  printf("Matrice terrain             Matrice pointeur perso\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      printf("%d ",map[i][j].land);

    }
    printf("          " );

    for(j=0;j<N;j++){
      printf("%u ",map[i][j].personnage);

    }

    printf("\n");
  }

}


void init_map_1(carellage_t map[N][N]){  //Initialise une map par défault

  int i,j;

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      map[i][j].land = 1;
      map[i][j].personnage=NULL;
    }
  }



}

void init_map_f(carellage_t map[N][N]){  //Initialise une map depuis un fichier
  init_map_1(map);
  int x,y,l;

  FILE * sauvegarde;

  sauvegarde = fopen("save.txt","r");

      while(!feof(sauvegarde)){
          fscanf(sauvegarde,"%d %d %d",&x,&y,&l);
          
          map[y][x].land = l;

      }



}

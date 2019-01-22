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


void init_map(){  //Initialise une map par défault
  carellage_t map[N][N];
  int i,j;

  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      map[i][j].land = 1;
      map[i][j].personnage=NULL;
    }
  }

  afficher_map(map);

}

/*void init_map_f(){  //Initialise une map depuis un fichier
  carellage_t map[N][N];


  afficher_map(map);

}
*/

#include "fonctions.h"
#include "map.h"

#define N 10


void afficher_map(carellage_t map[N][N]){
  int i,j;

  printf("Matrice terrain             Matrice pointeur perso\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      switch (map[i][j].land) {
        case 0: printf(BLK"%d "RESET,map[i][j].land);break;
        case 1: printf(GRN"%d "RESET,map[i][j].land);break;
        case 2: printf(BLU"%d "RESET,map[i][j].land);break;
        case 3: printf(RED"%d "RESET,map[i][j].land);break;
        case 4: printf(MAG"%d "RESET,map[i][j].land);break;
        case 5: printf(YEL"%d "RESET,map[i][j].land);break;
        default: printf(WHT"%d"RESET,map[i][j].land);break;
      }
    }
    printf("          ");

    for(j=0;j<N;j++){
      if(map[i][j].personnage == NULL)
        printf(BLK"🔳"RESET);
      else
        printf("%s",map[i][j].personnage->pp);

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

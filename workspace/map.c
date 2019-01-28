#include "fonctions.h"
#include "map.h"

#define N 10


void afficher_map(carte_t * pt_m){
  int i,j;

  printf("Matrice terrain             Matrice pointeur perso\n");
  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      switch (pt_m->land) {
        case 0: printf(BLK"%d "RESET,pt_m->land);break;
        case 1: printf(GRN"%d "RESET,pt_m->land);break;
        case 2: printf(BLU"%d "RESET,pt_m->land);break;
        case 3: printf(RED"%d "RESET,pt_m->land);break;
        case 4: printf(MAG"%d "RESET,pt_m->land);break;
        case 5: printf(YEL"%d "RESET,pt_m->land);break;
        default: printf(WHT"%d"RESET,pt_m->land);break;
      }
    }
    printf("          ");

    for(j=0;j<N;j++){
      if(pt_m->personnage == NULL)
        printf(BLK"🔳"RESET);


      else
        printf("%s",pt_m->personnage->pp);

    }

    printf("\n");
  }

}


void init_map(carte_t * pt_m){  //Initialise une map par défault

  int i,j;
  pt_m = malloc(sizeof(carte_t));
  int * p[N][N];
  pt_m->map=p;
  //pt_m->map = malloc(sizeof(dalle_t)*N*N);


  for(i=0;i<N;i++){
    for(j=0;j<N;j++){
      pt_m->map[i][j]->land = 1;
      pt_m->map[i][j]->personnage=NULL;
    }
}



}

void charger_partie(carte_t * pt_m){  //Charge un etat de la map depuis un fichier
  init_map(pt_m);
  /*int x,y,l;

  FILE * sauvegarde;

  sauvegarde = fopen("save.txt","r");

  while(!feof(sauvegarde)){
    fscanf(sauvegarde,"%d %d %d",&x,&y,&l);
    pt_m[y][x]->land = l;
  }

*/
}

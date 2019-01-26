#include "fonctions.h"
#include "personnage.h"

void pas_fini(){
  printf(YEL"%s\n", "sort non castable avant la prochaine lune \n"RESET);
}

void menu_choix(mage_t * m, carellage_t map[N][N]){
  int choix=-1;
    printf(MAG"+++++++++++++++++++\n" RESET);
    printf(MAG"%s\n" RESET, m->nom);
    printf(MAG"+++++++++++++++++++\n" RESET);
    printf(RED"+++++++++++++++++++\n" );
    printf("+ 1) boule de feu \n");
    printf("+ 2) make america great again \n");
    printf("+ 3) passer le tour \n");
    printf("++++++++++++++++++\n" RESET);

    while (choix <1 || choix >3) {
      scanf("%d",&choix);
    }

    switch(choix){
      case 1: boule_de_feu(m,map);break;
      case 2: pas_fini();break;
      case 3: printf("%s passe son tour", m->nom);break;
      default: pas_fini();break;
    }

}


void info_mage(mage_t *m){
  printf(CYN"+++++++++++++++++++\n" );
  printf("+ Nom   : %s \n", m->nom);
  printf("+ PV    : %d \n", m->pv);
  printf("+ pm    : %d \n", m->pm);
  printf("+ force : %d \n", m->force);
  printf("+ px    : %d \n", m->px);
  printf("+ py    : %d \n", m->py);
  printf("+++++++++++++++++++\n"RESET);
}

/*
void player(){
}
*/

void kombat(mage_t * m1, mage_t * m2, carellage_t map[N][N]){
  while (m1->pv>0 && m2->pv>0 ){
    if (m1->pv > 0 ){
      afficher_map(map);
      info_mage(m1);
      info_mage(m2);
      menu_choix(m1,map);
    }
    else{
      printf("%s est mort\n", m1->nom);
    }
    if (m2->pv > 0 ){
      afficher_map(map);
      info_mage(m1);
      info_mage(m2);
      menu_choix(m2,map);
    }
    else{
      printf("%s est mort\n", m2->nom);
    }
    /*afficher_map(map);*/
  }
  afficher_map(map);
  info_mage(m1);
  info_mage(m2);
}






























/**/

#include "fonction.h"

void pas_fini(){
  printf(YEL"%s\n", "sort non castable avant la prochaine lune \n"RESET);
}

void menu_choix(mage_t * m){
  int choix=-1;
    printf(RED"+++++++++++++++++++\n" );
    printf("+ 1) boule de feu \n");
    printf("+ 2) make america great again \n");
    printf("+ 3) passer le tour \n")
    printf("++++++++++++++++++\n" RESET);

    while (choix <1 && choix >3) {
      scanf("%d\n", choix);
    }

    switch(choix){
      case 1: boule_feu(m);
      case 2: pas_fini();
      case 3: pas_fini();
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


void kombat(mage_t * m1, mage_t * m2){
  while (m1.pv>0 && m1.pv>0 ){
    menu_choix(m1);
    menu_choix(m2);
  }
}

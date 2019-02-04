#include "fonctions.h"
#include "personnage.h"

void pas_fini(){
  printf(YEL"%s\n", "sort non castable avant la prochaine lune \n"RESET);
}

void cast_mage_noir(personnage_t * m, carte_t * pt_m){
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
    case 1: boule_de_feu(m,pt_m);break;
    case 2: pas_fini();break;
    case 3: printf("%s passe son tour", m->nom);break;
    default: pas_fini();break;
  }
}

void cast_mage_blanc(personnage_t * _personnage, carte_t * pt_m){
  int choix=-1;
  printf(MAG"+++++++++++++++++++\n" RESET);
  printf(MAG"%s\n" RESET, _personnage->nom);
  printf(MAG"+++++++++++++++++++\n" RESET);
  printf(RED"+++++++++++++++++++\n" );
  printf("+ 1) soin \n");
  printf("+ 2) cure \n");
  printf("+ 3) passer le tour \n");
  printf("++++++++++++++++++\n" RESET);

  while (choix <1 || choix >3) {
    scanf("%d",&choix);
  }

  switch(choix){
    case 1: soin(_personnage, pt_m);break;
    case 2: pas_fini();break;
    case 3: printf("%s passe son tour", _personnage->nom);break;
    default: pas_fini();break;
  }
}

void menu_choix(personnage_t * _personnage, carte_t * pt_m){

  switch (_personnage->classe) {
    case mage_noir: cast_mage_noir(_personnage,pt_m); break;
    case mage_blanc: cast_mage_blanc(_personnage,pt_m); break;
    default: printf(YEL"\nclasse non répertorié\ndsl\n" RESET );
  }


}


void info_personnage(personnage_t *m){
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

void kombat(personnage_t * m1, personnage_t * m2, carte_t * pt_m){
  while (m1->pv>0 && m2->pv>0 ){
    if (m1->pv > 0 ){
      afficher_map(pt_m);
      info_personnage(m1);
      info_personnage(m2);
      menu_choix(m1,pt_m);
    }
    else{
      printf("%s est mort\n", m1->nom);
    }
    if (m2->pv > 0 ){
      afficher_map(pt_m);
      info_personnage(m1);
      info_personnage(m2);
      menu_choix(m2,pt_m);
    }
    else{
      printf("%s est mort\n", m2->nom);
    }

  }
  afficher_map(pt_m);
  info_personnage(m1);
  info_personnage(m2);
}






























/**/

#include "fonctions.h"
#include "personnage.h"

void pas_fini(){
  printf(YEL"%s\n", "sort non castable avant la prochaine lune \n"RESET);
}

int phase_premiere(personnage_t * _personnage, carte_t * pt_m){
  int choix = -1;
  do{
    printf(MAG"+++++++++++++++++++\n" RESET);
    printf(MAG"%s\n" RESET, _personnage->nom);
    printf(MAG"+++++++++++++++++++\n" RESET);
    printf(RED"+++++++++++++++++++\n" );
    printf("+ 1) Attaquer \n");
    printf("+ 2) Se Deplacer \n");
    printf("+ 3) Utiliser un objet \n");
    printf("+ 4) Passer le tour \n");
    printf("++++++++++++++++++\n" RESET);

    scanf("%d",&choix);
  }while(choix <1 || choix >4);

  return(choix);

}


int phase_attaque(personnage_t * _personnage, carte_t * pt_m){
  int choix=-1;
  do{
    printf(MAG"+++++++++++++++++++\n" RESET);
    printf(MAG"%s\n" RESET, _personnage->nom);
    printf(MAG"+++++++++++++++++++\n" RESET);
    printf(RED"+++++++++++++++++++\n" );
    printf("+ 1) %s \n", _personnage->nom_spell[0]);
    printf("+ 2) cure \n");
    printf("+ 3) passer le tour \n");
    printf("+ 4) Retour (a coder) \n");
    printf("++++++++++++++++++\n" RESET);

    scanf("%d",&choix);
  }while (choix <1 || choix >4) ;


  return(choix);
}

void menu_choix(personnage_t * _personnage, carte_t * pt_m){
  int phase1=0, phase2=0;

  phase1 = phase_premiere(_personnage, pt_m);

  switch(phase1){
    case 1: phase2 = phase_attaque(_personnage, pt_m);
            switch(phase2){
              case 1: _personnage->tab_spell[0](_personnage, pt_m);break;
              case 2: pas_fini();break;
              case 3: printf(YEL"%s passe son tour"RESET, _personnage->nom);break;
              default: pas_fini();break;
            }
            break;
    case 2: deplacement(_personnage, pt_m);break;
    case 3: pas_fini();break;
    case 4: printf(YEL"%s passe son tour\n"RESET, _personnage->nom);break;
    default: pas_fini();break;
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

void kombat(personnage_t * m1, personnage_t * m2, carte_t * pt_m){
  while (m1->pv>0 && m2->pv>0 ){
    if (m1->pv > 0 ){
      afficher_map(pt_m);
      info_personnage(m1);
      /*info_personnage(m2);*/
      menu_choix(m1,pt_m);
    }
    else{
      printf("%s est mort\n", m1->nom);
    }
    if (m2->pv > 0 ){
      afficher_map(pt_m);
      /*info_personnage(m1);*/
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

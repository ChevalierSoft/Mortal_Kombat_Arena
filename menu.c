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
  int choix=-1, i=0;

    do{
      i=0;
      printf(MAG"+++++++++++++++++++\n" RESET);
      printf(MAG"%s\n" RESET, _personnage->nom);
      printf(MAG"+++++++++++++++++++\n" RESET);
      printf(RED"+++++++++++++++++++\n" );
      if (_personnage->est_sheep == 0){
        for(;i < _personnage->nb_spell; i++){
          printf("+ %d) %s \n", i+1, _personnage->nom_spell[i]);
        }
      }
      else
        i=_personnage->nb_spell;


      printf("+ %d) passer le tour \n",++i);
      printf("+ %d) Retour\n", ++i);

      printf("++++++++++++++++++\n" RESET);

      scanf("%d",&choix);
      if(choix == _personnage->nb_spell + 2)
        return 10;
    }while (choix <1 || choix > _personnage->nb_spell + 2) ;/*+2 pour passer le tour et retour*/
      return(choix);
  }



void menu_choix(personnage_t * _personnage, carte_t * pt_m){
  int phase1=0, phase2=0;


do{ /*tant que le retour n'est pas demandé*/
  phase1 = phase_premiere(_personnage, pt_m);
  phase2=0;
    switch(phase1){

      case 1: phase2 = phase_attaque(_personnage, pt_m);
                  if (phase2 <= _personnage->nb_spell)
                    _personnage->tab_spell[phase2-1](_personnage, pt_m);
                  else if(phase2==_personnage->nb_spell+1)
                    printf(YEL"%s passe son tour\n"RESET, _personnage->nom);
                  else if(phase2==_personnage->nb_spell+2)
                    pas_fini();
                	else{
                    printf("nani ?\n");
                  }break;
      case 2: phase2= deplacement(_personnage, pt_m);break;
      case 3: pas_fini();break;
      case 4: printf(YEL"%s passe son tour\n"RESET, _personnage->nom);break;
      default: pas_fini();break;
    }
  }while(phase2 == 10);
}

void info_personnage(personnage_t *p){
  printf(CYN"+++++++++++++++++++\n" );
  printf("+ Nom   : %s \n", p->nom);
  printf("+ PV    : %d "RESET, p->pv);if(p->est_shield)printf("+%d", p->est_shield);printf("\n");
  printf(CYN"+ pm    : %d \n", p->pm);
  printf("+ force : %d \n", p->force);
  printf("+ px    : %d \n", p->px);
  printf("+ py    : %d \n", p->py);

  printf("+++++++++++++++++++\n"RESET);
}

void kombat(personnage_t * m1, personnage_t * m2, carte_t * pt_m){
  /*while (m1->pv>0 && m2->pv>0 ){*/
  while(1){
    if (m1->pv > 0 ){
      afficher_map(pt_m);
      detection_etat();
      info_personnage(m1);
      menu_choix(m1,pt_m);

    }
    else{
      printf("%s est mort\n", m1->nom);
      break;
    }
    if (m2->pv > 0 ){
      afficher_map(pt_m);
      detection_etat();
      info_personnage(m2);
      menu_choix(m2,pt_m);
    }
    else{
      printf("\n%s est mort\n\n", m2->nom);
      break;
    }

  }
  afficher_map(pt_m);
  info_personnage(m1);
  info_personnage(m2);
}






























/**/

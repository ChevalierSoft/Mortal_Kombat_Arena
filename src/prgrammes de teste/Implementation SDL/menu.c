#include "fonctions.h"


void pas_fini(){
  printf(YEL"%s\n", "sort non castable avant la prochaine lune \n"RESET);
}

void menu_start(){
  printf("                                                                         \n");
  printf(MAG"@@@@@@@@@@   @@@  @@@   @@@@@@   @@@@@@@   @@@@@@@@  @@@  @@@   @@@@@@   \n");
  printf(   "@@@@@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@  @@@@@@@@  @@@@ @@@  @@@@@@@@  \n");
  printf(   "@@! @@! @@!  @@!  !@@  @@!  @@@  @@!  @@@  @@!       @@!@!@@@  @@!  @@@  \n");
  printf(   "!@! !@! !@!  !@!  @!!  !@!  @!@  !@!  @!@  !@!       !@!!@!@!  !@!  @!@  \n");
  printf(   "@!! !!@ @!@  @!@@!@!   @!@!@!@!  @!@!!@!   @!!!:!    @!@ !!@!  @!@!@!@!  \n");
  printf(CYN"!@!   ! !@!  !!@!!!    !!!@!!!!  !!@!@!    !!!!!:    !@!  !!!  !!!@!!!!  \n");
  printf(   "!!:     !!:  !!: :!!   !!:  !!!  !!: :!!   !!:       !!:  !!!  !!:  !!!  \n");
  printf(   ":!:     :!:  :!:  !:!  :!:  !:!  :!:  !:!  :!:       :!:  !:!  :!:  !:!  \n");
  printf(   ":::     ::    ::  :::  ::   :::  ::   :::   :: ::::   ::   ::  ::   :::  \n");
  printf(   " :      :     :   :::   :   : :   :   : :  : :: ::   ::    :    :   : :  \n\n"RESET);
  printf(   "                            PRESS ENTER\n"                                  );
  getchar();
}

int dbl_digit(char c){
  if (c>='0' && c<='9'){
    return(1);}
  return(0);
}

int menu_main(){
  int choix;
  printf(MAG" @@@@@@@@@@  @@@@@@@@ @@@  @@@ @@@  @@@\n");
  printf(   " @@! @@! @@! @@!      @@!@!@@@ @@!  @@@\n");
  printf(   " @!! !!@ @!@ @!!!:!   @!@@!!@! @!@  !@!\n");
  printf(CYN" !!:     !!: !!:      !!:  !!! !!:  !!!\n");
  printf(   "  :      :   : :: ::: ::    :   :.:: : \n\n"RESET);

  printf(YEL"1) Une machine\n");
  printf("2) Reseau (a implementer)\n");
  printf("3) Quitter\n"RESET);
  do{
    choix = getchar();
  }while( (!dbl_digit(choix)) || (choix < '1') || (choix > '3'));

  if(choix=='3'){
    printf(MAG"\n#######################################################################\n"RESET);
    exit(0);
  }

  return(choix-'0');
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


void menu_choix(personnage_t * sasuke, carte_t * pt_m){
  int phase1=0, phase2=0;
  do{ /*tant que le retour n'est pas demandé*/
    phase1 = phase_premiere(sasuke, pt_m);
    phase2 = 0;
      switch(phase1){

        case 1: phase2 = phase_attaque(sasuke, pt_m); /*si on choisi d'attaquer*/
                    if (phase2 <= sasuke->nb_spell){ /*lance le spell*/
                      /*void (*lel)(void *, void *);*/
                      /*sasuke->tab_spell[phase2-1](sasuke, pt_m);*/
                      getXY(sasuke, pt_m, (sasuke)->tab_spell[phase2-1]);
                      /*lel = sasuke->tab_spell[phase2-1];*/
                      /*getXY(sasuke, pt_m, lel);*/
                    }
                    else if(phase2==sasuke->nb_spell+1) /*passe le tour*/
                      printf(YEL"%s passe son tour\n"RESET, sasuke->nom);
                    else if(phase2==sasuke->nb_spell+2) /*un jour peut etre les objets*/
                      pas_fini();
                  	else;
                    break;
        case 2: getXY(sasuke, pt_m,&deplacement_cb);break;

        case 3: pas_fini();break;
        case 4: printf(YEL"%s passe son tour\n"RESET, sasuke->nom);break;
        default: pas_fini();break;
      }
  }while(phase2 == 10);
}

void info_personnage(personnage_t * p){
  printf(CYN"+++++++++++++++++++\n" );
  printf("+ Nom   : %s \n", p->nom);
  printf("+ PV    : %d "RESET, p->pv);if(p->est_shield)printf("+%d", p->est_shield);printf("\n");
  printf(CYN"+ pm    : %d \n", p->pm);
  printf("+ force : %d \n", p->force);
  printf("+ px    : %d \n", p->px);
  printf("+ py    : %d \n", p->py);

  printf("+++++++++++++++++++\n"RESET);
}

void backdash( personnage_t * ex){
  personnage_t * ex2;
  int i =0;
  en_tete();
  valeur_elt(&ex2);
  while(ex2 != ex && !liste_vide()){

    printf("Nom perso : %s\n",ex2->nom);
    suivant();
    valeur_elt(&ex2);
    i++;

  }

  if (liste_vide()){
    en_tete();
    printf("probleme de personnage free\n");
  }

}

int get_hp_team(int n){
  personnage_t * tmp;
	personnage_t * ex;/* personnage actuel*/

  int hp=0;
  valeur_elt(&ex);

	if(n==1){
    en_tete();
		valeur_elt(&tmp);
    /*printf("hero : %s , %s , pv : %d\n", tmp->nom, tmp->pp, tmp->pv);*/
		while(strcmp(tmp->pp, "👽")){
      /*printf("on avance #1\n");*/
      hp+=tmp->pv;
      suivant();
      valeur_elt(&tmp);
		}
    en_tete();
    valeur_elt(&tmp);
    while(tmp != ex){
      /*printf("on straff #1\n");*/
      suivant();
      valeur_elt(&tmp);
      /*sleep(1);*/
    }
	}
	else if (n==2){
    en_mid();
    suivant();
    valeur_elt(&tmp);
    /*printf("#2 hero : %s , %s , pv : %d\n", tmp->nom, tmp->pp, tmp->pv);*/
    while(!hors_liste()){
      hp+=tmp->pv;
      /*printf("on avance #2\n");*/
      suivant();
      valeur_elt(&tmp);
    }
    en_tete();
    valeur_elt(&tmp);
    while(tmp != ex){
      /*printf("on re avance #3\n");*/
      suivant();
      valeur_elt(&tmp);
      /*sleep(1);*/
    }
	}
	else
		printf("probleme avec le numero de la team %d \n", n);

  printf("HP Team %d : %d\n",n, hp);
	return(hp);
}

void kombat(carte_t * pt_m, int affSDL, ...){

  va_list liste;
  va_start(liste, 1);

  int partie_en_cours = 1;

  SDL_Renderer * renderer = va_arg(liste,SDL_Renderer *);

  /*verifier que la liste n'est pas vide pour lancer*/
  if (!liste_vide()&& partie_en_cours==1){
    /*bouleen de lancement de partie*/

    int team=1;


    /*barre de vie de la team*/
    int hp_team1=1, hp_team2=1;
    /*tmp prendra la valeur des personnages de la liste succecivement*/
    personnage_t * tmp;

    while(partie_en_cours){

      team = 1;
      /*affiche la liste des perso à chaque tours*/
  		afficher_liste();
    	en_tete();

  		/*boucle pour un tour*/
      while(!hors_liste()&& partie_en_cours == 1){

        detection_etat(pt_m);
        hp_team1=get_hp_team(1);
        hp_team2=get_hp_team(2);
        /*condition d'arret de la partie*/
        if (hp_team1<=0 || hp_team2<=0){
          partie_en_cours=0;
          break;
        }
        valeur_elt(&tmp);
        //Si on est au délimiteur
        if(!strcmp(tmp->pp, "👽"))team = 2;   /*  /!\   probleme ici pour les poisons et autre qui font le double des degats du au delimiteur */
        else if(tmp->pv>0) {

          afficher_map(pt_m);
    		  info_personnage(tmp);
          /*printf("infos affiches\n");*/
    		  /*menu_choix(tmp, pt_m);*/
          if(affSDL){
            partie_en_cours = jouer(renderer,tmp,pt_m);
            printf("Partie en cours : %d\n",partie_en_cours);


                //la capitulation
              /*if(team==1)
                hp_team1=0;
              else
                hp_team2=0;*/

            printf("HP de la team 1 : %d\n",hp_team1);
            printf("HP de la team 2 : %d\n",hp_team2);
          }
          else menu_choix(tmp, pt_m);
        }
        else{
          printf("%s est K.O\n",tmp->nom);
        }
        suivant();
      }

    }


  }
  printf("YOLOOOOOOOOOOOOOOOOOOOOOOOOOOOO\n");
  detection_etat(pt_m);
  printf("Detection etat ?\n");
  afficher_map(pt_m);
}






























/**/

#include<stdlib.h>
#include<stdio.h>
#include "personnage.h"
#include "liste_ptr.h"


t_element * ec;
t_element * drapeau;

void init_liste(){
  drapeau = malloc(sizeof(t_element));

  drapeau->succ = drapeau;
  drapeau->pred = drapeau;
  ec = drapeau;

}

int hors_liste(){
  return(ec == drapeau);
}

int liste_vide(){
  return(drapeau->succ == drapeau);

}

void en_tete(){
  if(!liste_vide())
    ec = drapeau->succ;
}


void en_mid(){
  if(!liste_vide()){
    en_tete();
    while(strcmp(ec->p->pp, "👽") && !hors_liste())
      ec = ec->succ;
  }
}


void en_queue(){
  if(!liste_vide())
    ec = drapeau->pred;
}

void suivant(){
  if(!hors_liste())
    ec = ec->succ;
  else
    ec = drapeau;
}

void precedent(){
  if(!hors_liste())
    ec = ec->pred;
  else
    ec = drapeau;
}

void valeur_elt(personnage_t ** p){ //Récupère un personnage et le mets dans une autre variable de type personnage
  if(!hors_liste()){
    *p=ec->p;
  }
}

void modif_elt(personnage_t * p){ //Ecrase un personnage de la liste et le remplace par le personnage en param
  //pas ouf cette fonction...
  if(!hors_liste()){
    ec->p = p;
  }
}

void oter_elt(){ //Free le pointeur sur un personnage de la liste

  if(!liste_vide()){

    t_element * popo= malloc(sizeof(popo));
    popo->succ=ec;

    detruire_spell(&ec->p);
    
    detruire_personnage(&ec->p);

    ec->pred->succ = ec->succ;
    ec->succ->pred = ec->pred;
    ec=ec->pred;
    free(popo->succ);
    free(popo);
  }
  else{
    printf("Liste vide!\n");
  }
}

void ajout_droit(personnage_t * p){ //Ajoute un personnage a la la suite de la liste
  t_element * nouv = malloc(sizeof(t_element));

  nouv->p = p;

  if(liste_vide()){
    
    nouv->succ = drapeau;
    nouv->pred = drapeau;
    drapeau->succ=nouv;
    drapeau->pred=nouv;
  }
  else{
    nouv->pred = ec;
    nouv->succ = ec->succ;
    ec->succ = nouv;
    nouv->succ->pred = nouv;
  }
}



void afficher_liste(){
  en_tete();
  printf(YEL"Affichage de la liste : \n"RESET);
  
  if(!liste_vide()){
    printf(CYN"#Team1\n"RESET);
    
    while(!hors_liste()){
      if(strcmp(ec->p->pp, "👽")){
        printf("| %s",ec->p->nom);
        if(ec->p->est_mort)printf("   KO");
        printf("\n");
      }
      else
        printf(MAG"#Team2\n"RESET);
      suivant();
    }
    printf("\n");
  }
  else
    printf("liste vide\n\n");
}

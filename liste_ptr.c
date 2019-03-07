#include<stdlib.h>
#include "personnage.h"


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

void en_queue(){
  if(!liste_vide())
    ec = drapeau->pred;

}

void suivant(){
  if(!hors_liste())
    ec = ec->succ;
}

void precedent(){
  if(!hors_liste())
    ec = ec->pred;
}

void valeur_elt(personnage_t ** p){ //Récupère un personnage et le mets dans une autre variable de type personnage
  if(!hors_liste()){
    *p=ec->p;
  }
}

void modif_elt(personnage_t * p){ //Ecrase un personnage de la liste et le remplace par le personnage en param
  if(!hors_liste()){
    ec->p = p;
  }
}

void oter_elt(){ //Free le pointeur sur un personnage de la liste
  if(!liste_vide()){
    ec->pred->succ = ec->succ;
    ec->succ->pred = ec -> pred;
    free(ec);
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
  }
  else{
    nouv->pred = ec;
    nouv->succ = ec->succ;
    ec->succ = nouv;
    nouv->succ->pred = nouv;
  }
}

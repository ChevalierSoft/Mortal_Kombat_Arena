#ifndef __AB_H__
#define __AB_H__

#include<stdio.h>
#include<stdlib.h>

typedef struct noeud {
	int val; 
	struct noeud *pere, *sag, *sad;
} t_noeud;

typedef struct noeud* t_ab;

typedef enum type_parcours { PREFIXE, INFIXE, POSTFIXE } t_type_parcours;


/****************************************
 * primitives de modification de la structure de l'arbre 
 ****************************************/
t_ab creer_arbre(int val, t_ab sag, t_ab sad, t_ab pere); /* renvoie l'arbre dont la racine vaut val, avec les sous-arbre sag et sad */
int supprimer_arbre(t_ab*);		/* supprimer le sous-arbre dont la racine est donnee en parametre  */
t_ab ajout_gauche(t_ab, int); 
t_ab ajout_droit(t_ab, int); 

/****************************************
 * primitives d'accès à la structure de l'arbre 
 ****************************************/
t_ab pere(t_ab); /* renvoie le pere s'il existe, NULL sinon */
t_ab sag(t_ab); /* renvoie le sous-arbre gauche s'il existe, NULL sinon */
t_ab sad(t_ab); /* renvoie le sous arbre droit s'il existe, NULL sinon */

/****************************************
 * primitives de vérification  
 ****************************************/
int arbre_vide(t_ab);			/* renvoie vrai si arbre vide, faux sinon */
int est_racine(t_ab); /*renvoie vrai si le noeud est une racine */
int est_feuille(t_ab); /*renvoie vrai si le noeud est une feuille */

/****************************************
 * primitives de modification de la valeur de la racine
 ****************************************/
int modif_racine(t_ab, int);	/* modifie la valeur de la racine de l'arbre */
int val_racine(t_ab, int*); 		/* renvoie la valeur de la racine de l'arbre */

/****************************************
 * primitives d'affichage 
 ****************************************/
int afficher_arbre(t_ab, t_type_parcours);
int afficher_arbre_prefixe(t_ab, int);
int afficher_arbre_infixe(t_ab, int );
int afficher_arbre_postfixe(t_ab, int);

void afficher_ancetres(t_ab a, char end);


int parcours_prefixe(t_ab, void (*)(int*));

#endif


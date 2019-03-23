#ifndef H_I
#define H_I


void init_hero(personnage_t * _personnage, int _px, int _py, char * _nom, carte_t * pt_m, int _classe);
void afficher_mage(personnage_t * marvin);
void detruire_personnage(personnage_t **);
void detruire_spell(personnage_t ** _personnage);
void detruire_liste(void);


#endif
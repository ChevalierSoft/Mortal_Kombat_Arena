

typedef struct elem{personnage_t * p; struct elem * succ;struct elem * pred;}t_element;



void init_liste();

int hors_liste();

int liste_vide();

void en_tete();
void en_queue();

void suivant();
void precedent();

void valeur_elt(personnage_t ** p); 

void modif_elt(personnage_t * p);

void oter_elt();

void ajout_droit(personnage_t * p);

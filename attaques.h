#ifndef H_A
#define H_A


void getXY						(void * personnage, void * pt_m, void f_cb(void * pp, void * map, int x, int y));

void soin_cb					(void * personnage, void * pt_m, int x, int y);

void cure_cb					(void * personnage, void * pt_m, int x, int yu);

void boule_de_feu_cb	(void * personnage, void * pt_m, int x, int y);

void summon_cb				(void * personnage, void * pt_m, int x, int y);

void sheep_cb					(void * personnage, void * pt_m, int x, int y);

void toxicite_cb			(void * personnage, void * pt_m, int x, int y);

void tourbilol_cb			(void * personnage, void * pt_m, int x, int y);

void shield_cb				(void * personnage, void * pt_m, int x, int y);

void fait_ton_greu_cb	(void * personnage, void * pt_m, int x, int y);

void arakiri (personnage_t * personnage, carte_t * pt_m);

void arakiri_cb (void * personnage, void * pt_m);

void jet_de_sable(personnage_t * personnage, carte_t * pt_m, int x, int y);

void jet_de_sable_cb(void * personnage,void * pt_m, int x, int y);

void detection_etat		(carte_t * pt_m);
void deplacement_cb		(void * personnage, void * pt_m, int x, int y);
int  range_detection	(personnage_t *_personnage, int range, int x, int y);


#endif

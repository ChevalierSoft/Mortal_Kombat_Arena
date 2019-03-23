#ifndef H_A
#define H_A


void getXY(void * p, void * m, void f_cb(void * pp, void * map, int xi, int yi));
void soin(personnage_t *_personnage,carte_t * pt_m);
void soin_cb(void *_personnage, void * pt_m);
void cure(personnage_t *_personnage, carte_t * pt_m);
void cure_cb(void *_personnage, void * pt_m);
void boule_de_feu(personnage_t *_personnage,carte_t * pt_m);
void boule_de_feu_cb(void *_personnage,void * pt_m);
void summon(personnage_t *_personnage, carte_t * pt_m);
void summon_cb(void *_personnage, void * pt_m);
void sheep(personnage_t *_personnage, carte_t * pt_m);
void sheep_cb(void *_personnage, void * pt_m);
void detection_etat(carte_t * pt_m);
int deplacement(personnage_t *_personnage, carte_t * pt_m);
int range_detection(personnage_t *_personnage,int range,int x,int y);
void toxicite(personnage_t * personnage,carte_t * pt_m);
void toxicite_cb(void * personnage,void * pt_m);
void tourbilol(personnage_t * personnage,carte_t * pt_m);
void tourbilol_cb(void * personnage,void * pt_m);
void shield(personnage_t * personnage,carte_t * pt_m);
void shield_cb(void * personnage,void * pt_m);
void fait_ton_greu(personnage_t * personnage,carte_t * pt_m);
void fait_ton_greu_cb(void * personnage,void * pt_m);


#endif
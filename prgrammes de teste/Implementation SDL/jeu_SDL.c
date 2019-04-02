#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "constantes_SDL.h"
#include "jeu_SDL.h"
#include "map_SDL.h"
#include "map.h"


void jouer(SDL_Renderer * renderer,carte_t * pt_m){

	 en_tete();

	 personnage_t * ex ;

	 valeur_elt(&ex);
	//Variables TTF
	TTF_Font * police = NULL;
	SDL_Color couleurNoire = {0,0,0};
	SDL_Surface * texteS;
	SDL_Texture * texte =NULL;


	int continuer=1;
	char spell[20];
	char * Menu[2]={"Attaquer","Deplacement"};
    //variables et structures pour la map
		int w_s,h_s;
		int i,j;
		int temp;
		int x_cursMAP,y_cursMAP,x_cursMENU,y_cursMENU,aMAP,bMAP,aMENU,bMENU;
		int numspell=0;
		int posyBouttons[ex->nb_spell+1];
		int BoutonAppuye=-1;
		int cameraX=0,cameraY=0;
		int cameraOff=30;
		int motionX=0,motionY=0;



		SDL_Event event;

		SDL_Rect sprite_rec;
		SDL_Rect test;
		SDL_Rect boutonPos;
		SDL_Rect position_p;
		SDL_Rect blanc;
		SDL_Rect cadrePos;

		SDL_Surface * surbrillance;
    SDL_Surface * sprites_s[6]= {NULL};
		SDL_Surface * persos_s[5] = {NULL};
		SDL_Surface * bouton[3] = {NULL};

		SDL_Surface * cadreS;

		SDL_Texture * sprite[6] = {NULL};
		SDL_Texture * perso[5] = {NULL};

		SDL_Texture * cadre = NULL;

		SDL_Texture * case_sub = NULL;

		SDL_Texture * boutonPasSurvole = NULL;
		SDL_Texture * boutonSurvole = NULL;
		SDL_Texture * boutonEnfonce = NULL;
		SDL_Texture * boutonActuel = NULL;



		w_s = 50; //weight et height des sprites
		h_s = 50;


			//Le TTF
		//chargement de la police
		police = TTF_OpenFont("augusta.ttf",25);



			//Les texutres
		//chargement de toues les etats de cases dans tableau sprites
    sprites_s[0]= IMG_Load("./sprite du projet/ca0.png");
    sprites_s[1]= IMG_Load("./sprite du projet/ca1.png");
    sprites_s[2]= IMG_Load("./sprite du projet/ca2.png");
    sprites_s[3]= IMG_Load("./sprite du projet/ca3.png");
    sprites_s[4]= IMG_Load("./sprite du projet/ca4.png");
    sprites_s[5]= IMG_Load("./sprite du projet/ca5.png");

	persos_s[2]= IMG_Load("./sprite du projet/Solaire.png");
	persos_s[4]= IMG_Load("./sprite du projet/doomguy.png");
	persos_s[3]= IMG_Load("./sprite du projet/NECRO.png");
	persos_s[0]= IMG_Load("./sprite du projet/VRAI_MARVIN.png");
	persos_s[1]= IMG_Load("./sprite du projet/ZUL.png");

	surbrillance = IMG_Load("./sprite du projet/surbrillance.png");

	bouton[0] = IMG_Load("./sprite du projet/bouton_pas_survole.png");
	bouton[1] = IMG_Load("./sprite du projet/bouton_survole.png");
	bouton[2] = IMG_Load("./sprite du projet/bouton_enfonce.png");

	cadreS = IMG_Load("./sprite du projet/cadre.png");

	cadre = SDL_CreateTextureFromSurface(renderer,cadreS);

	 sprite[0] = SDL_CreateTextureFromSurface(renderer,sprites_s[0]);
	 sprite[1] = SDL_CreateTextureFromSurface(renderer,sprites_s[1]);
	 sprite[2] = SDL_CreateTextureFromSurface(renderer,sprites_s[2]);
	 sprite[3] = SDL_CreateTextureFromSurface(renderer,sprites_s[3]);
	 sprite[4] = SDL_CreateTextureFromSurface(renderer,sprites_s[4]);
	 sprite[5] = SDL_CreateTextureFromSurface(renderer,sprites_s[5]);


	 perso[0] = SDL_CreateTextureFromSurface(renderer,persos_s[0]);
	 perso[1] = SDL_CreateTextureFromSurface(renderer,persos_s[1]);
	 perso[2] = SDL_CreateTextureFromSurface(renderer,persos_s[2]);
	 perso[3] = SDL_CreateTextureFromSurface(renderer,persos_s[3]);
	 perso[4] = SDL_CreateTextureFromSurface(renderer,persos_s[4]);

	 boutonPasSurvole = SDL_CreateTextureFromSurface(renderer,bouton[0]);
	 boutonSurvole = SDL_CreateTextureFromSurface(renderer,bouton[1]);
	 boutonEnfonce = SDL_CreateTextureFromSurface(renderer,bouton[2]);

	 boutonActuel = boutonPasSurvole;

	case_sub = SDL_CreateTextureFromSurface(renderer,surbrillance);
	if(SDL_SetTextureAlphaMod(case_sub,250)<0){
		printf("ALERTE ROUGE !! ALERTE ROUGE !! %s\n",SDL_GetError());
	}



	//Liberation des surfaces
	for (i = 0 ; i < 5 ; i++)
		SDL_FreeSurface(persos_s[i]);

	for (i = 0 ; i < 6 ; i++)
		SDL_FreeSurface(sprites_s[i]);

	for (i = 0 ; i < 2 ; i++)
		SDL_FreeSurface(bouton[i]);

	SDL_FreeSurface(surbrillance);
	SDL_FreeSurface(cadreS);



		//Position du cadre
			cadrePos.x = 0;
			cadrePos.y = (HAUTEUR_FENETRE - taille_sprite*3);
			cadrePos.w = LARGEUR_FENETRE;
			cadrePos.h = taille_sprite*3;


		//Position du bouton
	boutonPos.x = LARGEUR_FENETRE/3;
	boutonPos.y = (HAUTEUR_FENETRE - taille_sprite*3);




    // Chargement du niveau
  if (!chargerMap(pt_m))
      exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau




	while (continuer)

    {

        SDL_WaitEvent(&event);



        switch(event.type)

        {


        	case SDL_KEYDOWN:


                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer =0;
                        break;


                }
								if(event.key.keysym.sym == SDLK_UP){
									cameraY += 5;
								}
								if(event.key.keysym.sym == SDLK_DOWN){
									cameraY -= 5;
								}
								if(event.key.keysym.sym == SDLK_LEFT){
									cameraX += 5;
								}
								if(event.key.keysym.sym == SDLK_RIGHT){
									cameraX -= 5;
								}
                break;
            case SDL_MOUSEBUTTONUP:

						  	//Clic sur la map
								if(event.button.x <= LARGEUR_FENETRE && event.button.y <= HAUTEUR_FENETRE-3*taille_sprite){
									if(event.button.button == SDL_BUTTON_LEFT){
										x_cursMAP = event.button.x;
										y_cursMAP = event.button.y;
										aMAP = x_cursMAP/taille_sprite;
										bMAP = y_cursMAP/taille_sprite; //Récupère les coords de la case cliquée

										boutonActuel = boutonPasSurvole;

									}




								}
								//Clic dans menu
								if(event.button.x <= LARGEUR_FENETRE && event.button.y >= HAUTEUR_FENETRE-3*taille_sprite){

									if(event.button.x >= boutonPos.x && event.button.x <= boutonPos.x + boutonPos.w && event.button.y >= boutonPos.y && event.button.y <= boutonPos.y + ex->nb_spell*boutonPos.h){


										for(i=0;i<ex->nb_spell;i++){
											if(event.button.y >= posyBouttons[i] && event.button.y <= posyBouttons[i] + boutonPos.h)

												numspell = i;


										}
										if(numspell == 0){
											BoutonAppuye = 0;
										}


										boutonActuel = boutonEnfonce;

									}
									else{
										boutonActuel = boutonPasSurvole;									}



								}


								break;
						case SDL_MOUSEMOTION:
								//Dans la Map
								if(event.motion.x <= LARGEUR_FENETRE && event.motion.y <= HAUTEUR_FENETRE-3*taille_sprite){
									//Deplacement caméra

									//surbrillance watzafaque
									/*x_cursMAP = event.motion.x;
									y_cursMAP = event.motion.y;
									aMAP = x_cursMAP/taille_sprite;
									bMAP = y_cursMAP/taille_sprite;
									temp =pt_m->map[i][j]->land;
									pt_m->map[i][j]->land = -1;*/

								}
								//Dans le Menu
								else if(event.motion.y >=taille_sprite * nb_sprites_hauteur && event.motion.y <= HAUTEUR_FENETRE && event.motion.x <=LARGEUR_FENETRE){
									//Survolage de bouton
									/*if(event.motion.x >= boutonPos.x && event.motion.x <= boutonPos.x + boutonPos.w && event.motion.y >= boutonPos.y && event.motion.y <= boutonPos.y + boutonPos.h){
										boutonActuel = boutonSurvole;

									}
									else{
										boutonActuel = boutonPasSurvole;
									}*/


								}


								break;



            case SDL_QUIT:

                continuer = 0;
                break;

        }




				//PARTIE AFFICHAGE
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);

        //placement des objets à l'écran
        for(i=0;i<nb_sprites_largeur;i++){
            for(j=0;j<nb_sprites_hauteur;j++){

                sprite_rec.x = i * taille_sprite + cameraX;
                sprite_rec.y = j * taille_sprite + cameraY;
							 	sprite_rec.h = taille_sprite;
								sprite_rec.w = taille_sprite;

                switch(pt_m->map[i][j]->land){
                    case 0:
												SDL_QueryTexture(sprite[0], NULL, NULL, &w_s, &h_s);
												SDL_RenderCopy(renderer,sprite[0],NULL,&sprite_rec);

                        break;
                    case 1:
												SDL_QueryTexture(sprite[1], NULL, NULL, &w_s, &h_s);
                        SDL_RenderCopy(renderer,sprite[1],NULL,&sprite_rec);
                        break;
                    case 2:
												SDL_QueryTexture(sprite[2], NULL, NULL, &w_s, &h_s);
                      	SDL_RenderCopy(renderer,sprite[2],NULL,&sprite_rec);
                        break;
                    case 3:
												SDL_QueryTexture(sprite[3], NULL, NULL, &w_s, &h_s);
                        SDL_RenderCopy(renderer,sprite[3],NULL,&sprite_rec);
                        break;
                    case 4:
												SDL_QueryTexture(sprite[4], NULL, NULL, &w_s, &h_s);
                        SDL_RenderCopy(renderer,sprite[4],NULL,&sprite_rec);
                        break;
                    case 5:
												SDL_QueryTexture(sprite[5], NULL, NULL, &w_s, &h_s);
                        SDL_RenderCopy(renderer,sprite[5],NULL,&sprite_rec);
                        break;
										/*case -1:

												map[aMAP][bMAP] = temp;
												break;*/


                }





            }


        }


				//Affichage des personages
				personnage_t * stck;


				en_tete();

				while(!hors_liste()){

					valeur_elt(&stck);

					position_p.x = stck->px * taille_sprite + cameraX;
					position_p.y = stck->py * taille_sprite + cameraY;

					switch(stck->classe){

							case 0:

									SDL_QueryTexture(perso[0], NULL, NULL, &(position_p.w), &(position_p.h));
									SDL_RenderCopy(renderer,perso[0],NULL,&position_p);

									break;
							case 1:
									SDL_QueryTexture(perso[1], NULL, NULL, &(position_p.w), &(position_p.h));
									SDL_RenderCopy(renderer,perso[1],NULL,&position_p);
									break;
							case 2:
									SDL_QueryTexture(perso[2], NULL, NULL, &(position_p.w), &(position_p.h));
									SDL_RenderCopy(renderer,perso[2],NULL,&position_p);
									break;
							case 3:
									SDL_QueryTexture(perso[3], NULL, NULL, &(position_p.w), &(position_p.h));
									SDL_RenderCopy(renderer,perso[3],NULL,&position_p);
									break;
							case 4:
									SDL_QueryTexture(perso[4], NULL, NULL, &(position_p.w), &(position_p.h));
									SDL_RenderCopy(renderer,perso[4],NULL,&position_p);
									break;
							default:
									break;


							/*case -1:

									map[a][b] = temp;
									break;*/


					}


					suivant();
				}
				//retour au personnage initial(personnage actif)
				backdash(ex);

				//Affichage du menu
				SDL_QueryTexture(cadre,NULL,NULL,&(cadrePos.w),&(cadrePos.h));
				SDL_RenderCopy(renderer,cadre,NULL,&cadrePos);

				if(BoutonAppuye == -1){
					for(i=0;i<2;i++){

						texteS = TTF_RenderText_Solid(police,Menu[i],couleurNoire);
						SDL_DestroyTexture(texte);
						texte = SDL_CreateTextureFromSurface(renderer,texteS);

						SDL_QueryTexture(boutonActuel,NULL,NULL,&(boutonPos.w), &(boutonPos.h));
						SDL_QueryTexture(texte,NULL,NULL,NULL,NULL);

						SDL_RenderCopy(renderer,boutonActuel,NULL,&boutonPos);
						SDL_RenderCopy(renderer,texte,NULL,&boutonPos);
						posyBouttons[i]=boutonPos.y;

						boutonPos.y += i+1 * boutonPos.h;
						strcpy(spell,"");
					}
					boutonPos.y =  (HAUTEUR_FENETRE - taille_sprite*3);
				}
				else if(BoutonAppuye == 0){
					for(i=0;i<ex->nb_spell;i++){


						sprintf(spell,"%s",ex->nom_spell[i]);


						texteS = TTF_RenderText_Solid(police,spell,couleurNoire);
						SDL_DestroyTexture(texte);
						texte = SDL_CreateTextureFromSurface(renderer,texteS);


						SDL_QueryTexture(boutonActuel,NULL,NULL,&(boutonPos.w), &(boutonPos.h));
						SDL_QueryTexture(texte,NULL,NULL,NULL,NULL);

						SDL_RenderCopy(renderer,boutonActuel,NULL,&boutonPos);
						SDL_RenderCopy(renderer,texte,NULL,&boutonPos);
						posyBouttons[i]=boutonPos.y;

						boutonPos.y += i+1 * boutonPos.h;
						strcpy(spell,"");



					}
					boutonPos.y =  (HAUTEUR_FENETRE - taille_sprite*3);
				}






				SDL_RenderPresent(renderer);

	}

	//destruction de toutes les textures chargées
	for(i= 0;i < 6;i++) {
		SDL_DestroyTexture(sprite[i]);
	}

	for(i= 0;i < 5;i++) {
		SDL_DestroyTexture(perso[i]);
	}


	SDL_DestroyTexture(boutonPasSurvole);
	SDL_DestroyTexture(boutonSurvole);
	SDL_DestroyTexture(boutonEnfonce);
	SDL_DestroyTexture(boutonActuel);

	SDL_DestroyTexture(case_sub);
	SDL_DestroyTexture(texte);
	SDL_DestroyTexture(cadre);


	TTF_CloseFont(police);
}

#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "constantes.h"
#include "jeu.h"
#include "map.h"

void jouer(SDL_Renderer * renderer){


	SDL_Event event;
	SDL_Rect positionm1,positionm2;

	int continuer=1;
    //variables et structures pour la map
		int w_s,h_s;
		int i,j;
		int temp;
		int x_curs,y_curs,a,b;
    int map[nb_sprites_largeur][nb_sprites_hauteur] = {0};
    SDL_Rect sprite;
		SDL_Surface * surbrillance = SDL_CreateRGBSurface(w_s,h_s, 100, 32, 0, 0, 0, 50);
		SDL_Texture * case_sub;
    SDL_Surface *sprites_s[6]= {NULL};
		SDL_Surface * persos_s[5] = {NULL};

		w_s = 50; //weight et height des sprites
		h_s = 50;

		SDL_FillRect(surbrillance,&sprite,SDL_MapRGB(surbrillance->format,255,255,255));
		case_sub = SDL_CreateTextureFromSurface(renderer,surbrillance);

		//chargement de toues les etats de cases dans tableau sprites
    sprites_s[0]= IMG_Load("./sprite du projet/ca0.png");
    sprites_s[1]= IMG_Load("./sprite du projet/ca1.png");
    sprites_s[2]= IMG_Load("./sprite du projet/ca2.png");
    sprites_s[3]= IMG_Load("./sprite du projet/ca3.png");
    sprites_s[4]= IMG_Load("./sprite du projet/ca4.png");
    sprites_s[5]= IMG_Load("./sprite du projet/ca5.png");

	persos_s[0]= IMG_Load("./sprite du projet/Solaire.png");
	persos_s[1]= IMG_Load("./sprite du projet/doomguy.png");
	persos_s[2]= IMG_Load("./sprite du projet/NECRO.png");
	persos_s[3]= IMG_Load("./sprite du projet/VRAI_MARVIN.png");
	persos_s[4]= IMG_Load("./sprite du projet/ZUL.png");


	SDL_Texture * sprite0 = SDL_CreateTextureFromSurface(renderer,sprites_s[0]);
	SDL_Texture * sprite1 = SDL_CreateTextureFromSurface(renderer,sprites_s[1]);
	SDL_Texture * sprite2 = SDL_CreateTextureFromSurface(renderer,sprites_s[2]);
	SDL_Texture * sprite3 = SDL_CreateTextureFromSurface(renderer,sprites_s[3]);
	SDL_Texture * sprite4 = SDL_CreateTextureFromSurface(renderer,sprites_s[4]);
	SDL_Texture * sprite5 = SDL_CreateTextureFromSurface(renderer,sprites_s[5]);


	SDL_Texture * perso0 = SDL_CreateTextureFromSurface(renderer,persos_s[0]);
	SDL_Texture * perso1 = SDL_CreateTextureFromSurface(renderer,persos_s[1]);
	SDL_Texture * perso2 = SDL_CreateTextureFromSurface(renderer,persos_s[2]);
	SDL_Texture * perso3 = SDL_CreateTextureFromSurface(renderer,persos_s[3]);
	SDL_Texture * perso4 = SDL_CreateTextureFromSurface(renderer,persos_s[4]);



	//Liberation des surfaces
	for (i = 0 ; i < 5 ; i++)
		SDL_FreeSurface(persos_s[i]);

	for (i = 0 ; i < 6 ; i++)
		SDL_FreeSurface(sprites_s[i]);

	positionm1.x = (((0/4)/taille_sprite)*taille_sprite)+22;
	positionm1.y = (((480/4)/taille_sprite)*taille_sprite)+22;
	positionm2.x = (((640/4)/taille_sprite)*taille_sprite)+22;
	positionm2.y = (((480/4)/taille_sprite)*taille_sprite)+22;

    // Chargement du niveau
    if (!chargerMap(map))
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
                break;
            case SDL_MOUSEBUTTONUP:  //Lors d'un clic gauche, le perso se déplace vers les coords du clic
                if(event.button.button == SDL_BUTTON_LEFT){
									x_curs = event.motion.x;
									y_curs = event.motion.y;
									a = x_curs/taille_sprite;
									b = y_curs/taille_sprite; //Récupère les coords de la case cliquée
                  /*if(map[a][b] == un personnage){
											afficher les cases ou il peut se déplacer
												si on clique sur l'une de ses cases
													déplacer le personnage sur cette case
									}*/
                }
								/*
								 			Lignes servant à placer le perso sur la case cliquée
								positionm1.x = ((event.button.x/taille_sprite)*taille_sprite)+22;
								positionm1.y = ((event.button.y/taille_sprite)*taille_sprite)+22
								*/


                break;
						case SDL_MOUSEMOTION:
								x_curs = event.motion.x;
								y_curs = event.motion.y;
								a = x_curs/taille_sprite;
								b = y_curs/taille_sprite;
								temp = map[a][b];
								map[a][b] = -1;

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

                sprite.x = i * taille_sprite;
                sprite.y = j * taille_sprite;
							 	sprite.h = taille_sprite;
								sprite.w = taille_sprite;

                switch(map[i][j]){
                    case 0:
												SDL_QueryTexture(sprite0, NULL, NULL, &w_s, &h_s);
												SDL_RenderCopy(renderer,sprite0,NULL,&sprite);

                        break;
                    case 1:
												SDL_QueryTexture(sprite1, NULL, NULL, &w_s, &h_s);
                        SDL_RenderCopy(renderer,sprite1,NULL,&sprite);
                        break;
                    case 2:
												SDL_QueryTexture(sprite2, NULL, NULL, &w_s, &h_s);
                      	SDL_RenderCopy(renderer,sprite2,NULL,&sprite);
                        break;
                    case 3:
												SDL_QueryTexture(sprite3, NULL, NULL, &w_s, &h_s);
                        SDL_RenderCopy(renderer,sprite3,NULL,&sprite);
                        break;
                    case 4:
												SDL_QueryTexture(sprite4, NULL, NULL, &w_s, &h_s);
                        SDL_RenderCopy(renderer,sprite4,NULL,&sprite);
                        break;
                    case 5:
												SDL_QueryTexture(sprite5, NULL, NULL, &w_s, &h_s);
                        SDL_RenderCopy(renderer,sprite5,NULL,&sprite);
                        break;
										case -1:
												SDL_QueryTexture(case_sub, NULL, NULL, &w_s, &h_s);
												SDL_RenderCopy(renderer,case_sub,NULL,&sprite);


                }



            }


        }



			SDL_QueryTexture(perso0, NULL, NULL, &(positionm1.w), &(positionm1.h));
			SDL_QueryTexture(perso1, NULL, NULL, &(positionm2.w), &(positionm2.h));
			SDL_RenderCopy(renderer,perso0,NULL,&positionm1);
			SDL_RenderCopy(renderer,perso1,NULL,&positionm2);

			map[a][b] = temp;


			SDL_RenderPresent(renderer);

    }

		//destruction de toutes les textures chargées
		SDL_DestroyTexture(sprite0);
		SDL_DestroyTexture(sprite1);
		SDL_DestroyTexture(sprite2);
		SDL_DestroyTexture(sprite3);
		SDL_DestroyTexture(sprite4);
		SDL_DestroyTexture(sprite5);

		SDL_DestroyTexture(perso0);
		SDL_DestroyTexture(perso1);
		SDL_DestroyTexture(perso2);
		SDL_DestroyTexture(perso3);
		SDL_DestroyTexture(perso4);

		SDL_DestroyTexture(case_sub);




}

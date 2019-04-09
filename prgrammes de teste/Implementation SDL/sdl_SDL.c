#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "jeu_SDL.h"
#include "constantes_SDL.h"

void main_menu(SDL_Renderer * renderer,SDL_Texture* texture,SDL_Rect position);

int main( int argc, char* args[] ) {

	SDL_Window *ecran = NULL;
	SDL_Texture *menu = NULL;
	SDL_Rect position;





 	if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :

    {

       fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur

       exit(EXIT_FAILURE); // On quitte le programme

    }
	if(TTF_Init()==-1) {
	   printf("TTF_Init: %s\n", TTF_GetError());
	   exit(2);
	}





    ecran = SDL_CreateWindow("MK Arena",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,LARGEUR_FENETRE,HAUTEUR_FENETRE,SDL_WINDOW_RESIZABLE);
    if(ecran == NULL){
    	fprintf(stderr, "Impossible de charger le mode vidéo : %s\n",SDL_GetError());
    	exit(EXIT_FAILURE);
    }

		SDL_Renderer *renderer = SDL_CreateRenderer(ecran, -1, 0);


		menu = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STATIC, 1024, 768);
		menu = IMG_LoadTexture(renderer,"menu.png");

    position.x = 0;
		position.y = 0;
		position.w = LARGEUR_FENETRE;
		position.h = HAUTEUR_FENETRE;


		main_menu(renderer,menu,position);


		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(ecran);
	TTF_Quit();
 	SDL_Quit();
 	return 0;
 }



void main_menu(SDL_Renderer * renderer,SDL_Texture * menu,SDL_Rect position)

{

    int continuer = 1;

    SDL_Event event;

		while (continuer)

    {

        SDL_WaitEvent(&event);

        switch(event.type)

        {
            /*case SDL_MOUSEBUTTONUP:
                if(event.button.x > 207 && event.button.x < 450 && event.button.y > 308 && event.button.y < 398)
                    jouer(renderer);
                    break;
                break;*/
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer =0;
                        break;
                    case SDLK_KP_1:
                        jouer(renderer);
                        break;
                }
                break;



            case SDL_QUIT:

                continuer = 0;
                break;

        }

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);
				int w = LARGEUR_FENETRE;
				int h = HAUTEUR_FENETRE;
				SDL_QueryTexture(menu, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STATIC, &w, &h);


				SDL_RenderCopy(renderer,menu,NULL,&position);


				SDL_RenderPresent(renderer);

    }
		SDL_DestroyTexture(menu);

}

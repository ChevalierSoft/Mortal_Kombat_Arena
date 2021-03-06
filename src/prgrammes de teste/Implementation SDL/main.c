#include "fonctions.h"



void main_menu(SDL_Renderer * renderer,SDL_Texture* menu,SDL_Rect position,carte_t * pt_m){
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
                    //lancement de la partie
                      kombat(pt_m,1,renderer);


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


int main(int argc, char const **argv) {


  int affSDL=0, option=0;

  while ((option = getopt (argc, argv, "s")) != -1){
    if (option == 's'){
      affSDL = 1;
      break;
    }
  }
  /*---------------------------------------------------*/
  carte_t * pt_m= malloc(sizeof(carte_t));
  //on crée une liste de perso
  init_liste();
  printf("CHARGEMENT DE LA PARTIE :\n");
  //on charge la map
  charger_partie(pt_m);

  //on charge les persos
  load_perso(pt_m);

  /*---------------------------------------------------*/
  if (affSDL){

    printf("MK_Arena GUI\n");


    SDL_Window *ecran = NULL;
  	SDL_Texture *menu = NULL;
  	SDL_Rect position;

   	if (SDL_Init(SDL_INIT_VIDEO) == -1) { // Démarrage de la SDL. Si erreur :
         fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
         exit(EXIT_FAILURE); // On quitte le programme
      }
  	if(TTF_Init()==-1) {
  	   printf("TTF_Init: %s\n", TTF_GetError());
  	   exit(2);
  	}



    ecran = SDL_CreateWindow("MK Arena",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,LARGEUR_FENETRE,HAUTEUR_FENETRE,SDL_WINDOW_RESIZABLE);
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

    SDL_RenderSetLogicalSize(renderer, HAUTEUR_FENETRE, LARGEUR_FENETRE);

    main_menu(renderer,menu,position,pt_m);

    SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(ecran);
	  TTF_Quit();
 	  SDL_Quit();

  }
  else{
    menu_start();
    menu_main();
    if(!affSDL)
      kombat(pt_m, affSDL);
  }




  //fonction pour free tous les persos de la liste
  detruire_liste();
  //free la map
  map_detruire(&pt_m);
  afficher_liste();
  printf(RED"\n+++++++++++++++++++++++++++++++++++++++++++++++++++\n"RESET);

  return 0;

}

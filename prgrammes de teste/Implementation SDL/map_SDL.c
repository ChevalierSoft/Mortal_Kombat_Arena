#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "constantes_SDL.h"
#include "fonctions.h"



int chargerMap(carte_t * pt_m)
{
    FILE* save = NULL;
    char lignesave[nb_sprites_largeur * nb_sprites_hauteur + 1] = {0};
    int i = 0, j = 0;
    int x,y,l;

    save = fopen("save/m_save.txt", "r");
    if (save == NULL)
        return 0;

    while(!feof(save)){
        fscanf(save,"%d %d %d",&x,&y,&l);
        pt_m->map[x][y]->land= l;
    }


    fclose(save);
    return 1;
}

/*int sauvegarderMap(int map[][nb_sprites_hauteur])
{
    FILE* save = NULL;
    int i = 0, j = 0;

    save = fopen("save.txt", "w");
    if (save == NULL)
        return 0;

    for (i = 0 ; i < nb_sprites_largeur ; i++)
    {
        for (j = 0 ; j < nb_sprites_hauteur ; j++)
        {
            fprintf(save, "%d", map[j][i]);
        }
    }

    fclose(save);
    return 1;
}*/

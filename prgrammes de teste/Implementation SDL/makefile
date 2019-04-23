

CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image
INCLUDES=-I${SDLINC_DIR}

PROG=../../bin/MK_Arena_SDL



MK_Arena_SDL: jeu_SDL.c main.c attaques.c init_structure.c menu.c map.c liste_ptr.c map_SDL.c load_perso.c
	${CC} -o ${PROG} jeu_SDL.c map_SDL.c main.c attaques.c init_structure.c menu.c map.c liste_ptr.c load_perso.c ${LIBS} ${INCLUDES}

clean:
	rm -f ${PROG}
	rm -f *.o

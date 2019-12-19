#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "gestionAffichage.h"


int main(int argc, char **argv) {
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    //initPlateau();
    afficheMenuJeu(ecran);
    return 0;
}

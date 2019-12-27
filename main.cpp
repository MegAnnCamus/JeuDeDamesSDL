#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"gestionAffichage.h"

blackTile caseNoir;
whiteTile caseBlanc;
whiteTile caseHighlight;
whitePawn pionBlanc;
blackPawn pionNoir;
plateau plateauDeJeu;
joueur joueur1,joueur2;
int nbClic = 0;

int main(int argc, char **argv) {
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    afficheMenuJeu(ecran);
    return 0;
}

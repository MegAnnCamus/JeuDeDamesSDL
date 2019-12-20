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

int main(int argc, char **argv) {
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    joueur j1,j2;
    //strcpy(j1.nom, "Jane");
    //strcpy(j2.nom, "Toto");

    plateauDeJeu = initPlateau(j1,j2);
    afficheMenuJeu(ecran);
    return 0;
}

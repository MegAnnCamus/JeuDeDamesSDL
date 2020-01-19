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
//pour savoir si premier ou deuxième clic
int nbClic;
//pour savoir si un tour est en cours
int tourEnCoursMain;
//pour savoir si le coup joué est valide
int coupOkMain;

int main(int argc, char **argv) {
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);
    nbClic = 0;
    coupOkMain = 0;
    tourEnCoursMain = FALSE;
    afficheMenuJeu(ecran);
    //afficheVictoire(ecran,'B');
    return 0;
}

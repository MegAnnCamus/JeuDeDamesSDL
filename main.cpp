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

//pour savoir si premier ou deuxi�me clic
int nbClic = 0;
//pour savoir si un joueur est en train de r�aliser une action
int coupEnCoursMain = FALSE;
//liste des coups possibles
coup* coupsPossiblesMain;
//case de d�part d'une rafle
int caseDepartMain;
//pour v�rifier si on clique sur le m�me pion que l'on vient de d�placer
int caseIntermediaireMain;

int main(int argc, char **argv) {
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    afficheMenuJeu(ecran);
    //afficheVictoire(ecran,'B');
    return 0;
}

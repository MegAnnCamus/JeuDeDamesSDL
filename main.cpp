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
int nbClic = 0;
//pour savoir si un joueur est en train de réaliser une action
int coupEnCoursMain = FALSE;
//liste des coups possibles
coup* coupsPossiblesMain;
//case de départ d'une rafle
int caseDepartMain;
//pour vérifier si on clique sur le même pion que l'on vient de déplacer
int caseIntermediaireMain;

int main(int argc, char **argv) {
    SDL_Surface *ecran = NULL;
    SDL_Init(SDL_INIT_VIDEO);

    afficheMenuJeu(ecran);
    //afficheVictoire(ecran,'B');
    return 0;
}

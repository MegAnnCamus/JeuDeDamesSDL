#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"plateau.h"
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
    for(int i=0;i<51;i++){
        fprintf(stdout,"Case num %d : libre %d\n",plateauDeJeu.cases[i].notation,plateauDeJeu.cases[i].isLibre);
        if(plateauDeJeu.cases[i].isLibre==FALSE){
            fprintf(stdout,"Couleur : %c \n",plateauDeJeu.cases[i].pion.couleur);
        }
    }
    afficheMenuJeu(ecran);
    return 0;
}
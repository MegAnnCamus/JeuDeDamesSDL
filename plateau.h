#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"deplacement.h"

//initialisation du plateau en début de partie
plateau initPlateau(joueur j1, joueur j2);

//case plateau selon coordonées cliquées
casePlateau getCasePlateau(int x, int y, plateau board);

//mise à jour du plateau après un coup
void miseAjour(coup coupJoueur, plateau *board);

//pour déterminer si la partie est terminée
int partieTerminee(plateau board);

//teste si la case c est dans liste
int coupDansListe(casePlateau c, casePlateau *liste, int tailleListe);
//retourne le nombre de coups dans la liste
int nombreCoupsDansListe(coup *liste);

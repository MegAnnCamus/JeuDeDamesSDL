#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"deplacement.h"

//initialisation du plateau en d�but de partie
plateau initPlateau(joueur j1, joueur j2);

//case plateau selon coordon�es cliqu�es
casePlateau getCasePlateau(int x, int y, plateau board);

//mise � jour du plateau apr�s un coup
void miseAjour(coup coupJoueur, plateau *board);

//pour d�terminer si la partie est termin�e
int partieTerminee(plateau board);

//teste si la case c est dans liste
int coupDansListe(casePlateau c, casePlateau *liste, int tailleListe);
//retourne le nombre de coups dans la liste
int nombreCoupsDansListe(coup *liste);

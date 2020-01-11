#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"plateau.h"
#include"constantes.h"
#include"structuresSDL.h"

//Gestion du menu
int constructMenu(SDL_Surface* ecran, TTF_Font* font);
void afficheMenuJeu(SDL_Surface* ecran);

//Affichage écrans de victoire
int constructVictoire(SDL_Surface* ecran, TTF_Font* font,int couleurVictorieuse);
void afficheVictoire(SDL_Surface *ecran, int couleurVictorieuse);

//Pour saisir les noms des joueurs
void saisieNom(SDL_Surface *ecran, int gameStart, joueur *player);

//affichage plateau interface graphique
void affichePlateauSDL(SDL_Surface* ecran);
//affichage panneau de droite (infos de jeu)
void afficheRightPanel(SDL_Surface* ecran, joueur j1, joueur j2, joueur tour);

//gestion clic
int* clicPlateau(SDL_Event evenement);
casePlateau highlightPionClic(int *tab);

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"constantes.h"
#include"structuresSDL.h"

//Gestion du menu
int constructMenu(SDL_Surface* ecran, TTF_Font* font);
void afficheMenuJeu(SDL_Surface* ecran);

//affichage plateau interface graphique
void affichePlateauSDL();
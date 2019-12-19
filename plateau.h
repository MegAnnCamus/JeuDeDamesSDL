#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"constantes.h"
#include"structuresLogiques.h"

plateau initPlateau(joueur j1, joueur j2);
casePlateau getCasePlateau(int x, int y, plateau board);
void miseAjour(coup coupJoueur, plateau *board);

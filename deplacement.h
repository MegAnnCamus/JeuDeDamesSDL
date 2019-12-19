#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"constantes.h"
#include"structuresLogiques.h"

int deplacerPion(int oldPosition, int newPosition, plateau *board);
int prendrePion(int position, plateau *board);

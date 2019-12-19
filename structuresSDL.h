#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>

/** Structure definissant une case noire */
typedef struct blackTile{
	int isLibre;
	int tileNumber;
	SDL_Rect position;
	SDL_Surface *surface;
} blackTile;

/** Structure definissant une case blanche */
typedef struct whiteTile{
	int isLibre;
	int tileNumber;
	SDL_Rect position;
	SDL_Surface *surface;
} whiteTile;

/** Structure definissant un pion blanc */
typedef struct whitePawn{
	int isDame;
	SDL_Surface *surface;
	SDL_Rect position;
} whitePawn;

/** Structure definissant un pion noir */
typedef struct blackPawn{
	int isDame;
	SDL_Surface *surface;
	SDL_Rect position;
} blackPawn;


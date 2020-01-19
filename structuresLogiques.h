#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>

typedef struct pion{
	char couleur;
	int isDame;
	int isHighlighted;
} pion;

typedef struct joueur{
	char* nom;
	char couleur;
} joueur;

typedef struct casePlateau{
    int x;
	int y;
	char couleur;
	int isLibre;
    int notation;
	int isHighlighted;
	pion pion;
} casePlateau;

typedef struct plateau{
    //Plateau : 50 cases noires numérotées de 01 à 50sur lesquelles on joue.
    //cases[0] : représente les cases blanches
	casePlateau cases[51];
	joueur j1;
	joueur j2;
	char tour; //couleur du joueur qui doit jouer le prochain coup
} plateau;

typedef struct coup{
	int oldCase;
	int newCase;
	char type; //Si le coup est un déplacement standard ou une prise
	int nbPrises;
	casePlateau prises[20]; //Les cases avec pions pris.
	casePlateau historiqueCases[20]; //Les cases sur lesquelles passe le pion lors d'un rafle
} coup;



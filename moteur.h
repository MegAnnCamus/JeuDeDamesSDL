#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

//Joue le coup pour le joueur courant.
//0 si le coup est invalide.
//1 si le coup est valide et termin�.
//2 si le mouvement fait partie d'un coup valide non termin� (rafle)
int jouerCoup(int depart, int arrivee);
//Pareil qu'au dessus mais prend en param�tres des coordonn�es
int jouerCoupCoordonnees(int x1, int y1, int x2, int y2);

//Joue sur la profondeur d'�valuation du min-max.
void setDifficulte(int i);

//d�bute un nouveau tour
int commencerTour();

//highlight les cases sur lesquelles on peut se d�placer en partant de c
int showDeplacementsPossibles(int c);
//idem qu'au dessus mais prend en param�tres les coordonn�es de la case
int showDeplacementsPossiblesCoordonnees(int x,int y);

//Met en surbrillance le meilleur coup � jouer en utilisant l'IA.
void showMeilleurCoup();

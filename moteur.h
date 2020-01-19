#include <stdio.h>
#include <stdlib.h>
#include "plateau.h"

//Joue le coup pour le joueur courant.
//0 si le coup est invalide.
//1 si le coup est valide et terminé.
//2 si le mouvement fait partie d'un coup valide non terminé (rafle)
int jouerCoup(int depart, int arrivee);
//Pareil qu'au dessus mais prend en paramètres des coordonnées
int jouerCoupCoordonnees(int x1, int y1, int x2, int y2);

//Joue sur la profondeur d'évaluation du min-max.
void setDifficulte(int i);

//débute un nouveau tour
int commencerTour();

//highlight les cases sur lesquelles on peut se déplacer en partant de c
int showDeplacementsPossibles(int c);
//idem qu'au dessus mais prend en paramètres les coordonnées de la case
int showDeplacementsPossiblesCoordonnees(int x,int y);

//Met en surbrillance le meilleur coup à jouer en utilisant l'IA.
void showMeilleurCoup();

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include "moteur.h"

//liste de coups possibles pour le pion sur la case c
coup* coupsPossiblesPion(const casePlateau c, const plateau board);
//liste des déplacements standards pour le pion sur le case c
coup* getDeplacementsStandardsPion(const casePlateau c, const plateau board);

//débute un nouveau tour
int commencerTour();

//liste des coups qu'un joueur peut faire
coup* getCoupsPossiblesJoueur(const joueur j, const plateau board);
//coup max parmi la liste
coup* getCoupsMax(const coup *cp);

//Retourne 0 si pas de pion à prendre sur la diagonale
//retourne le nulero de la case avec le pion à prendre sinon
int getPossibleCasePos(int c, int diag, plateau p);

//retourne la liste des coups possibles commençant par le coup c
coup * completerCoupDame(const coup c, int mvt, plateau p);
//lise des coups possibles avec la dame sur la case c
coup* coupsPossiblesDames(const casePlateau c, const plateau p);

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

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "plateau.h"

//liste de coups possibles pour le pion sur la case c
coup* coupsPossiblesPion(const casePlateau c, const plateau board);
//liste des coups qu'un joueur peut faire
coup* getCoupsPossiblesJoueur(const joueur j, const plateau board);

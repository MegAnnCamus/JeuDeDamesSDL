
//La fonction d'evaluation de l'algorithme MinMax.
//Renvoie un double compris entre -1 et 1 caracterisant un etat du plateau plus ou moins favorable au joueur courant.

#include <stdio.h>
#include <stdlib.h>
#include "regles.h"


//La fonction principale
//Retourne un double entre 1 (victoire du joueur courant) et -1 (victoire de l'adversaire).

double fct_eval(const plateau * p);


//Renvoie, pour une case occupee, sa valeur. Independamment du joueur auquel appartient le pion.

int valeur_case(const plateau * p, const case_plateau * c);


//Renvoie, pour une case occupee, son rang ie le numero de sa ligne. (depend du camp du pion)

int rang(const case_plateau * c);


//un pion isolé n'est pas sur un bord et n'a aucun pion de son camp present dans une case adjacente.

int est_isole(const plateau * p, const case_plateau * c, int rang);

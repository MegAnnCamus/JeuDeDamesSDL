#include "plateau.h"

//retourne le tableau des coups possible pour un coup donn�.
//c La case qui contient le pion de la recherche.
//p la plateau courant.

coup* coupsPossibles(const case_plateau c, const plateau p);


//retourne le tableau des coups possible pour le joueur donn�.
//j le joueur dont on chercher tout les coups
//p la plateau courant.

coup* getCoups(const joueur j, const plateau p);


//retourne les coups qui ont le max de prises possible.
//cp le tableau de tout les coups possibles

coup* getCoupsMax(const coup *cp);


//retourne les deplacements possibles du pion de la case donn�
//c la case ou est situ� le pion dont on va chercher les d�placements possibles.

coup* get_deplacements(const case_plateau c, const plateau p);


//La liste des coups possibles commen�ant par le coup c.
//mvt La diagonale du mouvement du coup pr�cedent.

coup * completer_coup_dame(const coup c, int mvt, plateau p);


//Retourne 0 si pas de cpions � prendre, la case sur laquelle se trouve le pion � prendre sinon.
//c Notation officielle de la case de d�part.
//diag Diagonale dans laquelle on recherche.

int get_possible_case_pos(int c, int diag, plateau p) ;


//Retourne 0 si liste 1 == liste2, sinon 1
//liste1 la premiere liste des coups
//liste2 la seconde liste des coups


int compare_coups(coup *liste1, coup *liste2);


//Retourne la case qui est en position x y dans p
//x la position en abscisse
//la position en ordonn�e
//p le plateau courant

case_plateau get_case_plateau_silent(int x, int y, plateau p);

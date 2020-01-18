#include "gestionCoup.h"

coup* coupsPossiblesPion(const casePlateau c, const plateau board){
    coup *cpossibles = calloc(NBCOUPS, sizeof(coup));
    plateau finalBoard = board;
    int nbCoup = 0;
	casePlateau currentCase = c;
	char adversaire = (c.pion.couleur == BLANC) ? NOIR : BLANC;

	//Premier coup
	coup currentCoup;
	currentCoup.oldCase = currentCase.notation;
	currentCoup.nbPrises = 0;
	currentCoup.type = PRISE;
	currentCoup.historiqueCases[currentCoup.nbPrises++] = currentCase;

	int dansRafle = FALSE;
	int fini = FALSE;
	int dernierePosition = 0;

	//cases sur lesquelles il faudra éviter de repasser depuis
	//la position initiale
	casePlateau casesToAvoidDepart[5];
	int nbCasesToAvoidDepart = 0;

	//cases sur lesquelles il faudra éviter de repasser
	//pendant la rafle
	casePlateau casesToAvoidParcours[5];
	int nbCasesToAvoidParcours = 0;

}

coup* getCoupsPossiblesJoueur(const joueur j, const plateau board){




}

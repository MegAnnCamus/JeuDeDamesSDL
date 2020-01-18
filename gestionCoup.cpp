#include "gestionCoup.h"


coup* getDeplacementsStandardsPion(const casePlateau c, const plateau board){
    coup *moves = (coup*)calloc(3, sizeof(coup));
	coup *d = moves;
	plateau finalBoard = board;

	if (c.pion.couleur == BLANC) { //si le pion sur la case est blanc : déplacements "vers le haut"
		casePlateau c1 = getCasePlateau(c.x - 1, c.y - 1, finalBoard); //case haut gauche
		if ((c1.notation != 0) && c1.isLibre == TRUE) { //si la case est libre et qu'elle est dans le plateau
			coup nouveauCoup;
			nouveauCoup.oldCase = c.notation;
			nouveauCoup.newCase = c1.notation;
			nouveauCoup.type = STANDARD;
			//ajout du coup à la liste
			*(d++) = nouveauCoup;
		}
		casePlateau c2 = getCasePlateau(c.x + 1, c.y - 1, finalBoard); //case haut droite
		if ((c2.notation != 0) && c2.isLibre == TRUE) {
			coup nouveauCoup;
			nouveauCoup.oldCase = c.notation;
			nouveauCoup.newCase = c2.notation;
			nouveauCoup.type = STANDARD;
			*(d++) = nouveauCoup;
		}
	} else { //si le pion sur la case est noir : déplacements "vers le bas"
		casePlateau c1 = getCasePlateau(c.x - 1, c.y + 1, finalBoard); //case bas gauche
		if ((c1.notation != 0) && c1.isLibre == TRUE) {
			coup nouveauCoup;
			nouveauCoup.oldCase = c.notation;
			nouveauCoup.newCase = c1.notation;
			nouveauCoup.type = STANDARD;
			*(d++) = nouveauCoup;
		}
		casePlateau c2 = getCasePlateau(c.x + 1, c.y + 1, finalBoard); //case bas droite
		if ((c2.notation != 0) && c2.isLibre == TRUE) {
			coup nouveauCoup;
			nouveauCoup.oldCase = c.notation;
			nouveauCoup.newCase = c2.notation;
			nouveauCoup.type = STANDARD;
			printf("\n");
			*(d++) = nouveauCoup;
		}
	}

	/*MARQUAGE DE LA FIN DU TABLEAU*/
	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	*(d++) = foo;

	return moves;
}


coup* coupsPossiblesPion(const casePlateau c, const plateau board){
    coup *cpossibles = (coup*)calloc(NB_COUPS_MAX, sizeof(coup));
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
	//on marque la case qu'on va visiter
	casePlateau casesToAvoidDepart[5];
	int nbCasesToAvoidDepart = 0;

	//cases sur lesquelles il faudra éviter de repasser
	//pendant la rafle
	//on marque les pions alentour qu'on a visité pour ne pas repasser dessus
	casePlateau casesToAvoidParcours[5];
	int nbCasesToAvoidParcours = 0;

	casePlateau aTester = getCasePlateau(currentCase.x-1,currentCase.y-1,finalBoard);

	/*TEST DES PRISES POSSIBLES */
	while(fini==FALSE) {
		/* DIAGONALE HAUT GAUCHE */
		if((aTester.isLibre == FALSE) //si un pion est présent sur la case
				&& (aTester.pion.couleur == adversaire) //si le pion est de la couleur de l'adversaire
				&& (isPrenable(aTester.notation,&finalBoard) == TRUE) //si le pion est prenable
				&& ((getCasePlateau(aTester.x-1, aTester.y-1, finalBoard).isLibre == TRUE) //si la case derrière le pion est libre de base...
						|| coupDansListe(getCasePlateau(aTester.x-1, aTester.y-1, finalBoard),currentCoup.historiqueCases,currentCoup.nbPrises) == TRUE) //...ou que l'on a pris le pion qui se trouvait dessus
				&& (coupDansListe(aTester, currentCoup.prises, currentCoup.nbPrises) == FALSE) //si l'on est pas déjà passé au dessus du pion à tester (interdit)
				&& (getCasePlateau(aTester.x-1, aTester.y-1, finalBoard).notation != 0) //si la case se trouve toujours dans le plateau (cas où on se trouve sur le bord)
				&& (aTester.notation != dernierePosition) //si on ne revient pas en arrière (interdit)
				&& (coupDansListe(aTester, casesToAvoidParcours, nbCasesToAvoidParcours) == FALSE)) { //si la case ne fait pas partie des cases à éviter
			if((currentCase.notation == currentCoup.oldCase) //si on est sur la case de départ du coup
					&& (currentCoup.nbPrises <= 1) // et que l'on a pas encore fait de prise
					&& (coupDansListe(aTester, casesToAvoidDepart, nbCasesToAvoidDepart) == TRUE)) {
				//si la case à tester fait partie des cases à éviter depuis la case de départ du coup
				break;
			}
			else {
				dansRafle = TRUE;
				dernierePosition = 0;
				if ((currentCase.notation == currentCoup.oldCase) //si on se trouve sur la case de départ
						&& (currentCoup.nbPrises <= 1)) {
                    //ajout de la case à tester dans les cases à éviter pendant la rafle
					casesToAvoidDepart[nbCasesToAvoidDepart++] = aTester;
				}
				//mise à jour de la position : on se trouve maintenant sur la case derrière le pion mangé
				//qui se trouve sur aTester
				currentCase = getCasePlateau(aTester.x-1, aTester.y-1, finalBoard);
				currentCoup.newCase = currentCase.notation;
				//rajout de aTester dans la liste des prises
				currentCoup.prises[currentCoup.nbPrises - 1] = aTester;
				//rajout de la case sur laquelle on est dans l'historique des cases visitées
				currentCoup.historiqueCases[currentCoup.nbPrises++] = currentCase;

                //on recommence le test sur la DIAGONALE HAUT GAUCHE
				aTester = getCasePlateau(currentCase.x-1,currentCase.y-1, finalBoard);
			}
		} //si aTester fait partie des case à éviter, on teste une autre diagonale
		else {
			aTester = getCasePlateau(currentCase.x+1,currentCase.y-1,finalBoard);
			/* DIAGONALE HAUT DROITE */
			if((aTester.isLibre == FALSE) //mêmes tests qu'au dessus
					&& (aTester.pion.couleur == adversaire)
					&& (isPrenable(aTester.notation,&finalBoard) == TRUE)
					&& ((getCasePlateau(aTester.x+1, aTester.y-1, finalBoard).isLibre == TRUE)
							|| coupDansListe(getCasePlateau(aTester.x+1, aTester.y-1, finalBoard), currentCoup.historiqueCases, currentCoup.nbPrises) == TRUE)
					&& (coupDansListe(aTester, currentCoup.prises, currentCoup.nbPrises) == FALSE)
					&& (getCasePlateau(aTester.x+1, aTester.y-1, finalBoard).notation != 0)
					&& (aTester.notation != dernierePosition)
					&& (coupDansListe(aTester, casesToAvoidParcours, nbCasesToAvoidParcours) == FALSE)) {
				if((currentCase.notation == currentCoup.oldCase)
						&& (currentCoup.nbPrises <= 1)
						&& (coupDansListe(aTester, casesToAvoidDepart, nbCasesToAvoidDepart) == TRUE)) {
					break;
				}
				else {
					dansRafle = TRUE;
					dernierePosition = 0;

					if ((currentCase.notation == currentCoup.oldCase)
						&& (currentCoup.nbPrises <= 1)){
						casesToAvoidDepart[nbCasesToAvoidDepart++] = aTester;
					}
					currentCase = getCasePlateau(aTester.x+1, aTester.y-1, finalBoard);
					currentCoup.newCase = currentCase.notation;
					currentCoup.prises[currentCoup.nbPrises - 1] = aTester;
					currentCoup.historiqueCases[currentCoup.nbPrises++] = currentCase;

					aTester = getCasePlateau(currentCase.x-1,currentCase.y-1, finalBoard);
				}
			} //si aTester fait partie des cases à éviter, on teste une autre diagonale
			else {
				aTester = getCasePlateau(currentCase.x-1,currentCase.y+1,finalBoard);
				/* DIAGONALE BAS GAUCHE */
				if((aTester.isLibre == FALSE) //mêmes tests qu'au dessus
						&& (aTester.pion.couleur == adversaire)
						&& (isPrenable(aTester.notation,&finalBoard) == TRUE)
						&& ((getCasePlateau(aTester.x-1, aTester.y+1, finalBoard).isLibre == TRUE)
								|| coupDansListe(getCasePlateau(aTester.x-1, aTester.y+1, finalBoard),currentCoup.historiqueCases,currentCoup.nbPrises) == TRUE)
						&& (coupDansListe(aTester, currentCoup.prises, currentCoup.nbPrises) == FALSE)
						&& (getCasePlateau(aTester.x-1, aTester.y+1, finalBoard).notation != 0)
						&& (aTester.notation != dernierePosition)
						&& (coupDansListe(aTester, casesToAvoidParcours, nbCasesToAvoidParcours) == FALSE)) {
					if((currentCase.notation == currentCoup.oldCase)
							&& (currentCoup.nbPrises <= 1)
							&& (coupDansListe(aTester, casesToAvoidDepart, nbCasesToAvoidDepart) == TRUE)) {
						break;
					}
					else {
						dansRafle = TRUE;
						dernierePosition = 0;
						if ((currentCase.notation == currentCoup.oldCase)
							&& (currentCoup.nbPrises <= 1)){
							casesToAvoidDepart[nbCasesToAvoidDepart++] = aTester;
						}
						currentCase = getCasePlateau(aTester.x-1, aTester.y+1, finalBoard);
						currentCoup.newCase = currentCase.notation;
						currentCoup.prises[currentCoup.nbPrises - 1] = aTester;
						currentCoup.historiqueCases[currentCoup.nbPrises++] = currentCase;

						aTester = getCasePlateau(currentCase.x-1,currentCase.y-1, finalBoard);
					}
				} //si aTester fait partie des cases à éviter, on teste une autre diagonale
				else {
					aTester = getCasePlateau(currentCase.x+1,currentCase.y+1,finalBoard);
					/* DIAGONALE BAS DROITE */
					if((aTester.isLibre == FALSE) //mêmes tests qu'au dessus
							&& (aTester.pion.couleur == adversaire)
							&& (isPrenable(aTester.notation,&finalBoard) == TRUE)
							&& ((getCasePlateau(aTester.x+1, aTester.y+1, finalBoard).isLibre == TRUE)
									|| coupDansListe(getCasePlateau(aTester.x+1, aTester.y+1, finalBoard),currentCoup.historiqueCases,currentCoup.nbPrises) == TRUE)
							&& (coupDansListe(aTester, currentCoup.prises, currentCoup.nbPrises) == FALSE)
							&& (getCasePlateau(aTester.x+1, aTester.y+1, finalBoard).notation != 0)
							&& (aTester.notation != dernierePosition)
							&& (coupDansListe(aTester, casesToAvoidParcours, nbCasesToAvoidParcours) == FALSE)) {
						if((currentCase.notation == currentCoup.oldCase)
								&& (currentCoup.nbPrises <= 1)
								&& (coupDansListe(aTester, casesToAvoidDepart, nbCasesToAvoidDepart) == TRUE)) {
							break;
						}
						else {
							dansRafle = TRUE;
							dernierePosition = 0;

							if ((currentCase.notation == currentCoup.oldCase)
								&& (currentCoup.nbPrises <= 1)){
								casesToAvoidDepart[nbCasesToAvoidDepart++] = aTester;
							}
							currentCase = getCasePlateau(aTester.x+1, aTester.y+1, finalBoard);
							currentCoup.newCase = currentCase.notation;
							currentCoup.prises[currentCoup.nbPrises - 1] = aTester;
							currentCoup.historiqueCases[currentCoup.nbPrises++] = currentCase;

							aTester = getCasePlateau(currentCase.x-1,currentCase.y-1, finalBoard);
						}
					}
					else { //enregistrement du coup
                        //mise à jour de la dernière position
						dernierePosition = currentCoup.prises[currentCoup.nbPrises - 2].notation;
						//ajout du coup à la liste des coups possibles
						if(dansRafle && currentCoup.oldCase != 0 && currentCoup.newCase != 0) {
							cpossibles[nbCoup++] = currentCoup;
							dansRafle = FALSE;
						}
						if(currentCoup.nbPrises <= 1) { //si il n'y a plus de prises
							fini = TRUE;
						}
						//retour en arrière
						casesToAvoidParcours[nbCasesToAvoidParcours++] = currentCoup.prises[currentCoup.nbPrises - 2];
						currentCoup.nbPrises--;
						currentCase = currentCoup.historiqueCases[currentCoup.nbPrises - 1];
						aTester = getCasePlateau(currentCase.x-1,currentCase.y-1, finalBoard);
					}
				}
			}
		}
	}
	/*TEST DES DEPLACEMENTS STANDARDS POSSIBLES */
	coup *deplacements = getDeplacementsStandardsPion(c, board);
	while((deplacements->oldCase != 0) && (deplacements->newCase != 0)) {
		cpossibles[nbCoup++] = *deplacements;
		deplacements++;
	}

	/* ON MARQUE LA FIN DU TABELAU */
	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	cpossibles[nbCoup++] = foo;
	return cpossibles;

}

//coup* getCoupsPossiblesJoueur(const joueur j, const plateau board){}

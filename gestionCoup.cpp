#include "gestionCoup.h"

extern int coupEnCoursMain;
extern coup* coupsPossiblesMain;

int commencerTour() {
	if (coupEnCoursMain == FALSE) {
		coupsPossiblesMain = getCoupsMax(getCoupsPossiblesJoueur(getJoueurPlateau(plateauDeJeu), plateauDeJeu)); //màj de la liste des coups possibles
		if (nombreCoupsDansListe(coupsPossiblesMain) == 0) { // si on ne peut pas jouer, on passe la main.
			if(plateauDeJeu.tour == plateauDeJeu.j1.couleur)
				plateauDeJeu.tour = plateauDeJeu.j2.couleur;
			else
				plateauDeJeu.tour = plateauDeJeu.j1.couleur;
			return 1;
		}
	}
}

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


int getPossibleCasePos(int c, int diag, plateau p) {
	int x = p.cases[c].x;
	int y = p.cases[c].y;
	switch (diag) {
	case 1:
		while (x > 0 && y > 0) { /*DIAG HAUT GAUCHE*/
			x--;
			y--;
			casePlateau aPrendre = getCasePlateau(x, y, p);
			if (!aPrendre.isLibre) { /* si on trouve une case non libre */
				if (aPrendre.pion.couleur != p.cases[c].pion.couleur) { /* soit elle à un pion adversaire */
					return getCasePlateau(x, y, p).notation;
				} else { /* soit un pion de la même couleur */
					return 0;
				}
			}
		}
		return 0;
		break;
	case 2:
		while (x <= 10 && y > 0) { /*DIAG HAUT DROITE*/
			x++;
			y--;
			casePlateau aPrendre = getCasePlateau(x, y, p);
			if (!aPrendre.isLibre) { /* si on trouve une case non libre */
				if (aPrendre.pion.couleur != p.cases[c].pion.couleur) { /* soit elle à un pion adversaire */
					return getCasePlateau(x, y, p).notation;
				} else { /* soit un pion de la même couleur */
					return 0;
				}
			}
		}
		return 0;
		break;
	case 3:
		while (x > 0 && y <= 10) { /*DIAG BAS GAUCHE*/
			x--;
			y++;
			casePlateau aPrendre = getCasePlateau(x, y, p);
			if (!aPrendre.isLibre) { /* si on trouve une case non libre */
				if (aPrendre.pion.couleur != p.cases[c].pion.couleur) { /* soit elle à un pion adversaire */
					return getCasePlateau(x, y, p).notation;
				} else { /* soit un pion de la même couleur */
					return 0;
				}
			}
		}
		return 0;
		break;
	case 4:
		while (x <= 10 && y <= 10) { /*DIAG BAS DROITE*/
			x++;
			y++;
			casePlateau aPrendre = getCasePlateau(x, y, p);
			if (!aPrendre.isLibre) { /* si on trouve une case non libre */
				if (aPrendre.pion.couleur != p.cases[c].pion.couleur) { /* soit elle à un pion adversaire */
					return getCasePlateau(x, y, p).notation;
				} else { /* soit un pion de la même couleur */
					return 0;
				}
			}
		}
		return 0;
		break;
	default:
		return 0;
		break;
	}
}


coup * completerCoupDame(const coup c, int mvt, plateau p) {
	coup * res = (coup*)calloc(100, sizeof(coup));
	int cpt_res = 0;
	plateau finalBoard;
	if (mvt == 1 || mvt == 4) { /*DIAGONALE HAUT GAUCHE OU BAS DROITE*/
		int diag2 = getPossibleCasePos(c.newCase, 2, p); // on cherche sur les diagonales perpendiculaires
		int diag3 = getPossibleCasePos(c.newCase, 3, p);
		if (diag2!=0) { // si on peut prendre un pion sur la diagonale haut droite
			casePlateau cPrise = p.cases[diag2];
			int x = cPrise.x + 1;
			int y = cPrise.y - 1;
			while (x <= 10 && y > 0 && getCasePlateau(x, y, p).isLibre == TRUE) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp = c;
				//ajout de la prise au coup
				cp.prises[cp.nbPrises] = cPrise;
				//on doit atterrir sur la case après la prise
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.nbPrises++;
				cp.historiqueCases[cp.nbPrises] = newCase;
				cp.newCase = newCase.notation;
				res[cpt_res++] = cp;

				if (getPossibleCasePos(newCase.notation, 1, p) /* si il n'y a pas d'aures prises sur la diagonale, on ajoute le coup */
				|| getPossibleCasePos(newCase.notation, 4, p)) {

					finalBoard = p;
					prendrePion(cPrise.notation, &finalBoard);
					deplacerPion(c.newCase,
							newCase.notation, &finalBoard);
					coup * coupsCompletes =
							completerCoupDame(cp, 2, finalBoard);
					int nbCoups = nombreCoupsDansListe(coupsCompletes);
					for (int i = 0; i < nbCoups; i++) {
						res[cpt_res++] = coupsCompletes[i];
					}
				}
				x++;
				y--;
			}
		}
		if (diag3!=0) { // si on peut prendre un pion sur la diagonale bas gauche
			casePlateau cPrise = p.cases[diag3];
			int x = cPrise.x - 1;
			int y = cPrise.y + 1;
			while (x > 0 && y <= 10 && getCasePlateau(x, y, p).isLibre==TRUE) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp = c;
				cp.prises[cp.nbPrises] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.nbPrises++;
				cp.historiqueCases[cp.nbPrises] = newCase;
				cp.newCase = newCase.notation;
				res[cpt_res++] = cp;
				if (!(getPossibleCasePos(newCase.notation, 1, p) /* si il n'y a pas d'aures prises sur la diagonale, on ajoute le coup */
				|| getPossibleCasePos(newCase.notation, 4, p))) {

					finalBoard = p;
					prendrePion(cPrise.notation, &finalBoard);
					deplacerPion(c.newCase,
							newCase.notation, &finalBoard);
					coup * coupsCompletes =
							completerCoupDame(cp, 3, finalBoard);
					int nbCoups = nombreCoupsDansListe(coupsCompletes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						res[cpt_res++] = coupsCompletes[i];
					}
				}
				x--;
				y++;
			}
		}
	} else { /*DIAGONALE HAUT DROITE OU BAS GAUCHE*/
		int diag1 = getPossibleCasePos(c.newCase, 1, p); // on cherche sur les diagonales perpendiculaires
		int diag4 = getPossibleCasePos(c.newCase, 4, p);
		if (diag1!=FALSE) { // si on peut prendre un pion sur la diagonale 1
			casePlateau cPrise = p.cases[diag1];
			int x = cPrise.x - 1;
			int y = cPrise.y - 1;
			while (x > 0 && y > 0 && getCasePlateau(x, y, p).isLibre==TRUE) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp = c;
				cp.prises[cp.nbPrises] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.nbPrises++;
				cp.historiqueCases[cp.nbPrises] = newCase;
				cp.newCase = newCase.notation;
				res[cpt_res++] = cp;
				if (!(getPossibleCasePos(newCase.notation, 2, p) /* si il n'y a pas d'aures prises sur la diagonale, on ajoute le coup */
				|| getPossibleCasePos(newCase.notation, 3, p))) {
					finalBoard = p;
					prendrePion(cPrise.notation, &finalBoard);
					deplacerPion(c.newCase,
							newCase.notation, &finalBoard);
					coup * coupsCompletes =
							completerCoupDame(cp, 1, finalBoard);
					int nbCoups = nombreCoupsDansListe(coupsCompletes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						res[cpt_res++] = coupsCompletes[i];
					}
				}
				x--;
				y--;
			}
		}
		if (diag4!=FALSE) { // si on peut prendre un pion sur la diagonale 3
			casePlateau cPrise = p.cases[diag4];
			int x = cPrise.x + 1;
			int y = cPrise.y + 1;
			while (x <= 10 && y <= 10 && getCasePlateau(x, y, p).isLibre==TRUE) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp = c;
				cp.prises[cp.nbPrises] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.nbPrises++;
				cp.historiqueCases[cp.nbPrises] = newCase;
				cp.newCase = newCase.notation;
				res[cpt_res++] = cp;

				if (!(getPossibleCasePos(newCase.notation, 2, p) /* si il n'y a pas d'aures prises sur la diagonale, on ajoute le coup */
				|| getPossibleCasePos(newCase.notation, 3, p))) {
					finalBoard = p;
					prendrePion(cPrise.notation, &finalBoard);
					deplacerPion(c.newCase,
							newCase.notation, &finalBoard);
					coup * coupsCompletes =
							completerCoupDame(cp, 4, finalBoard);
					int nbCoups = nombreCoupsDansListe(coupsCompletes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						res[cpt_res++] = coupsCompletes[i];
					}
				}
				x++;
				y++;
			}
		}
	}

	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	res[cpt_res++] = foo;

	return res;
}

coup* coupsPossiblesDames(const casePlateau c, const plateau p) {

	coup * cps = (coup*)calloc(NB_COUPS_MAX, sizeof(coup));
	plateau finalBoard = p;
	int nbCoup = 0;
	casePlateau currentCase = c;
	char adversaire = (c.pion.couleur == BLANC) ? NOIR : BLANC;

	/* conditions de départ */
	coup currentCoup;
	currentCoup.oldCase = currentCase.notation;
	currentCoup.nbPrises = 0;
	currentCoup.type = PRISE;
	currentCoup.historiqueCases[currentCoup.nbPrises++] = currentCase;

	/* pour signaler qu'on est dans une rafle */
	int newRafle = FALSE;
	int derniereRechercheFaite = FALSE; /* lorsqu'on revient sur la case de départ, on fait une derniere recherche */
	int fini = FALSE;
	int dernierePosition = 0;

	//cases sur lesquelles il faudra éviter de repasser depuis
	//on marque la case qu'on va visiter
	casePlateau casesToAvoid[5];
	int nbCasesToAvoid = 0;

	while (fini==FALSE) {
		/*DIAGONALE HAUT GAUCHE*/
		int casePrise = getPossibleCasePos(c.notation, 1, p);
		casePlateau caseDerriere = getCasePlateau(
				p.cases[casePrise].x - 1, p.cases[casePrise].y - 1, p);
		if (casePrise==FALSE || caseDerriere.isLibre==FALSE
				|| caseDerriere.notation == 0) { /* si la diagonale est vide, ou qu'on ne peut pas prendre le pion */
			int x = c.x - 1;
			int y = c.y - 1;
			while (x > 0 && y > 0 && getCasePlateau(x, y, p).isLibre==TRUE) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pion. */
				casePlateau newCase = getCasePlateau(x, y, p);
				if (newCase.notation != 0) {
					coup cp;
					cp.type = '-';
					cp.oldCase = c.notation;
					cp.nbPrises = 0;
					cp.newCase = newCase.notation;
					cps[nbCoup++] = cp; /* on ajoute tous les coups � la liste */
				}
				x--;
				y--;
			}

		} else { /* sinon, il y a un pion à prendre sur la diagonale */
			casePlateau cPrise = p.cases[casePrise];
			int x = cPrise.x - 1;
			int y = cPrise.y - 1;
			while (x > 0 && y > 0 && getCasePlateau(x, y, p).isLibre==TRUE) { /* dans ce cas, on parcours les cases de la diagonale derri�re la prise */
				coup cp;
				cp.type = PRISE;
				cp.oldCase = c.notation;
				cp.nbPrises = 1;
				cp.prises[0] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.historiqueCases[0] = c;
				cp.historiqueCases[1] = newCase;
				cp.newCase = newCase.notation;

				finalBoard = p;
				prendrePion(cPrise.notation, &finalBoard);
				deplacerPion(c.notation,
						newCase.notation, &finalBoard);

				cps[nbCoup++] = cp;

				if (getPossibleCasePos(newCase.notation, 2,
						finalBoard) || getPossibleCasePos(
						newCase.notation, 3, finalBoard)) { /* si il y a une prise possible sur la diagonale, on l'ajoute � la liste */
					coup * coupsCompletes =
							completerCoupDame(cp, 1, finalBoard);

					int nbCoups = nombreCoupsDansListe(coupsCompletes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						cps[nbCoup++] = coupsCompletes[i];
					}
					free(coupsCompletes);
				}
				x--;
				y--;
			}
		}
		/*DIAGONALE HAUT DROITE*/
		casePrise = getPossibleCasePos(c.notation, 2, p);
		caseDerriere = getCasePlateau(p.cases[casePrise].x + 1,
				p.cases[casePrise].y - 1, p);
		if (casePrise==FALSE || caseDerriere.isLibre==FALSE
				|| caseDerriere.notation == 0) { /* si la diagonale est vide */
			int x = c.x + 1;
			int y = c.y - 1;
			while (x <= 10 && y > 0 && getCasePlateau(x, y, p).isLibre==TRUE) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pion. */
				casePlateau newCase = getCasePlateau(x, y, p);
				if (newCase.notation != 0) {
					coup cp;
					cp.type = '-';
					cp.oldCase = c.notation;
					cp.nbPrises = 0;
					cp.newCase = newCase.notation;
					cps[nbCoup++] = cp; /* on ajoute tous les coups � la liste */
				}
				x++;
				y--;
			}

		} else { /* sinon, il y a un pion à prendre sur la diagonale */
			casePlateau cPrise = p.cases[casePrise];
			int x = cPrise.x + 1;
			int y = cPrise.y - 1;
			while (x <= 10 && y > 0 && getCasePlateau(x, y, p).isLibre==TRUE) { /* dans ce cas, on parcours les cases de la diagonale derri�re la prise */
				coup cp;
				cp.type = PRISE;
				cp.oldCase = c.notation;
				cp.nbPrises = 1;
				cp.prises[0] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.historiqueCases[0] = c;
				cp.historiqueCases[1] = newCase;
				cp.newCase = newCase.notation;

				finalBoard = p;
				prendrePion(cPrise.notation, &finalBoard);
				deplacerPion(c.notation,
						newCase.notation, &finalBoard);
				cps[nbCoup++] = cp;

				if (getPossibleCasePos(newCase.notation, 1,
						finalBoard) || getPossibleCasePos(
						newCase.notation, 4, finalBoard)) {

					coup * coupsCompletes =
							completerCoupDame(cp, 2, finalBoard);

					int nbCoups = nombreCoupsDansListe(coupsCompletes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						cps[nbCoup++] = coupsCompletes[i];
					}
					free(coupsCompletes);
				}
				x++;
				y--;
			}
		}
		/*DIAGONALE BAS GAUCHE*/
		casePrise = getPossibleCasePos(c.notation, 3, p);
		caseDerriere = getCasePlateau(p.cases[casePrise].x - 1,
				p.cases[casePrise].y + 1, p);
		if (casePrise==FALSE || caseDerriere.isLibre==FALSE
				|| caseDerriere.notation == 0) { /* si la diagonale est vide */
			int x = c.x - 1;
			int y = c.y + 1;
			while (x > 0 && y <= 10 && getCasePlateau(x, y, p).isLibre) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pion. */
				casePlateau newCase = getCasePlateau(x, y, p);
				if (newCase.notation != 0) {
					coup cp;
					cp.type = '-';
					cp.oldCase = c.notation;
					cp.nbPrises = 0;
					cp.newCase = newCase.notation;
					cps[nbCoup++] = cp; /* on ajoute tous les coups � la liste */
				}
				x--;
				y++;
			}

		} else { /* sinon, il y a un pion � prendre sur la diagonale */
			casePlateau cPrise = p.cases[casePrise];
			int x = cPrise.x - 1;
			int y = cPrise.y + 1;
			while (x > 0 && y <= 10 && getCasePlateau(x, y, p).isLibre==TRUE) { /* dans ce cas, on parcours les cases de la diagonale derri�re la prise */
				coup cp;
				cp.type = PRISE;
				cp.oldCase = c.notation;
				cp.nbPrises = 1;
				cp.prises[0] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.historiqueCases[0] = c;
				cp.historiqueCases[1] = newCase;
				cp.newCase = newCase.notation;

				finalBoard = p;
				prendrePion(cPrise.notation, &finalBoard);
				deplacerPion(c.notation,
						newCase.notation, &finalBoard);
				cps[nbCoup++] = cp;

				if (getPossibleCasePos(newCase.notation, 1,
						finalBoard) || getPossibleCasePos(
						newCase.notation, 4, finalBoard)) {
					coup * coupsCompletes =
							completerCoupDame(cp, 3, finalBoard);

					int nbCoups = nombreCoupsDansListe(coupsCompletes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						cps[nbCoup++] = coupsCompletes[i];
					}
					free(coupsCompletes);
				}
				x--;
				y++;
			}
		}
		/*DIAGONALE BAS DROITE*/
		casePrise = getPossibleCasePos(c.notation, 4, p);
		caseDerriere = getCasePlateau(p.cases[casePrise].x + 1,
				p.cases[casePrise].y + 1, p);
		if (casePrise==FALSE || caseDerriere.isLibre==FALSE
				|| caseDerriere.notation == 0) { /* si la diagonale est vide */
			int x = c.x + 1;
			int y = c.y + 1;
			while (x <= 10 && y <= 10 && getCasePlateau(x, y, p).isLibre==TRUE) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pion. */
				casePlateau newCase = getCasePlateau(x, y, p);
				if (newCase.notation != 0) {
					coup cp;
					cp.type = '-';
					cp.oldCase = c.notation;
					cp.nbPrises = 0;
					cp.newCase = newCase.notation;
					cps[nbCoup++] = cp; /* on ajoute tous les coups � la liste */
				}
				x++;
				y++;
			}

		} else { /* sinon, il y a un pion à prendre sur la diagonale */
			casePlateau cPrise = p.cases[casePrise];
			int x = cPrise.x + 1;
			int y = cPrise.y + 1;
			while (x <= 10 && y <= 10 && getCasePlateau(x, y, p).isLibre==TRUE) { /* dans ce cas, on parcours les cases de la diagonale derri�re la prise */
				coup cp;
				cp.type = PRISE;
				cp.oldCase = c.notation;
				cp.nbPrises = 1;
				cp.prises[0] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.historiqueCases[0] = c;
				cp.historiqueCases[1] = newCase;
				cp.newCase = newCase.notation;

				finalBoard = p;
				prendrePion(cPrise.notation, &finalBoard);
				deplacerPion(c.notation,
						newCase.notation, &finalBoard);
				cps[nbCoup++] = cp;

				if (getPossibleCasePos(newCase.notation, 2,
						finalBoard) || getPossibleCasePos(
						newCase.notation, 3, finalBoard)) { /* si il y a d'aures prises sur la diagonale */
					coup * coupsCompletes =
							completerCoupDame(cp, 4, finalBoard);

					int nbCoups = nombreCoupsDansListe(coupsCompletes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						cps[nbCoup++] = coupsCompletes[i];
					}
					free(coupsCompletes);
				}
				x++;
				y++;
			}
		}
		fini = TRUE;
	}
	//free(deplacements);
	/* MARQUAGE DE LA FIN DU TABLEAU*/
	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	cps[nbCoup++] = foo;
	return cps;
}

coup* getCoupsPossiblesJoueur(const joueur j, const plateau p) {
	coup *cp = (coup*)calloc(500, sizeof(coup));

	casePlateau c;
	int nbCoup = 0;
	int i;
	int k = 0;
	for (i = 1; i < 51; i++) { //parcours des cases du plateau
		c = p.cases[i];
		if ((c.isLibre==FALSE) && (c.pion.couleur == j.couleur)) { //si la case contient un pion du joueur j
			coup * aAjouter;
			if (c.pion.isDame) {
				aAjouter = coupsPossiblesDames(c, p);
			} else {
				aAjouter = coupsPossiblesPion(c, p);
			}
			//recopie des coups de ce pion dans cp
			while ((aAjouter[k].oldCase != 0) && (aAjouter[k].newCase != 0)) {
				cp[nbCoup++] = aAjouter[k++];
			}
			k = 0;
		}
	}
	/* MARQUAGE DE LA FIN DU TABLEAU */
	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	cp[nbCoup++] = foo;

	coup *result = (coup*)calloc(nbCoup, sizeof(coup));
	memcpy(&result, &cp, sizeof result);

	return result;
}

coup* getCoupsMax(const coup *cp) {

	int i = 0;
	coup *coupsMax = (coup*)calloc(NB_COUPS_MAX, sizeof(coup));
	int nbCoupsMax = 0;
	int nbPrisesMax = 0;

	while ((cp[i].oldCase != 0) && (cp[i].newCase != 0)) { //parcours pour trouver le nb de prises max
		if (cp[i].nbPrises > nbPrisesMax) {
			nbPrisesMax = cp[i].nbPrises;
		}
		i++;
	}
	i = 0;
	while ((cp[i].oldCase != 0) && (cp[i].newCase != 0)) { //on ne garde que les coups qui ont ce nb de prises
		if (cp[i].nbPrises == nbPrisesMax) {
			coupsMax[nbCoupsMax++] = cp[i];
		}
		i++;
	}

	/* MARQUAGE DE LA FIN DU TABLEAU */
	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	coupsMax[nbCoupsMax++] = foo;

	coup *result = (coup*)calloc(nbCoupsMax, sizeof(coup));
	memcpy(&result, &coupsMax, sizeof(result));
	return result;
}

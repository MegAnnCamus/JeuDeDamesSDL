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

int getPossibleCasePos(int c, int diag, plateau p) {
	int x = p.cases[c].x;
	int y = p.cases[c].y;
	switch (diag) {
	case 1:
		while (x > 0 && y > 0) {
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
		while (x <= 10 && y > 0) {
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
		while (x > 0 && y <= 10) {
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
		while (x <= 10 && y <= 10) {
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
	coup * res = calloc(100, sizeof(coup));
	int cpt_res = 0;
	plateau p_futur;
	if (mvt == 1 || mvt == 4) { // si on est dur la diagonale 1-4
		int diag2 = getPossibleCasePos(c.newCase, 2, p); // on cherche sur les diagonales perpendiculaires
		int diag3 = getPossibleCasePos(c.newCase, 3, p);
		if (diag2) { // si on peut prendre un pion sur la diagonale 2
			casePlateau cPrise = p.cases[diag2];
			int x = cPrise.x + 1;
			int y = cPrise.y - 1;
			while (x <= 10 && y > 0 && getCasePlateau(x, y, p).isLibre) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp = c;
				cp.prises[cp.nombre_prises] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.nombre_prises++;
				cp.chemin[cp.nombre_prises] = newCase;
				cp.newCase = newCase.notation;
				res[cpt_res++] = cp;

				if (getPossibleCasePos(newCase.notation, 1, p) /* si il n'y a pas d'aures prises sur la diagonale, on ajoute le coup */
				|| getPossibleCasePos(newCase.notation, 4, p)) {

					p_futur = p;
					plateau_prendre_pion(cPrise.notation, &p_futur);
					plateau_deplacer_pion(c.newCase,
							newCase.notation, &p_futur);
					coup * coups_completes =
							completerCoupDame(cp, 2, p_futur);
					int nbCoups = nombre_coups(coups_completes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						res[cpt_res++] = coups_completes[i];
					}
				}
				x++;
				y--;
			}
		}
		if (diag3) { // si on peut prendre un pion sur la diagonale 3
			casePlateau cPrise = p.cases[diag3];
			int x = cPrise.x - 1;
			int y = cPrise.y + 1;
			while (x > 0 && y <= 10 && getCasePlateau(x, y, p).isLibre) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp = c;
				cp.prises[cp.nombre_prises] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.nombre_prises++;
				cp.chemin[cp.nombre_prises] = newCase;
				cp.newCase = newCase.notation;
				res[cpt_res++] = cp;
				if (!(getPossibleCasePos(newCase.notation, 1, p) /* si il n'y a pas d'aures prises sur la diagonale, on ajoute le coup */
				|| getPossibleCasePos(newCase.notation, 4, p))) {

					p_futur = p;
					plateau_prendre_pion(cPrise.notation, &p_futur);
					plateau_deplacer_pion(c.newCase,
							newCase.notation, &p_futur);
					coup * coups_completes =
							completerCoupDame(cp, 3, p_futur);
					int nbCoups = nombre_coups(coups_completes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						res[cpt_res++] = coups_completes[i];
					}
				}
				x--;
				y++;
			}
		}
	} else { // sinon on est sur la diagonale 2-3
		int diag1 = getPossibleCasePos(c.newCase, 1, p); // on cherche sur les diagonales perpendiculaires
		int diag4 = getPossibleCasePos(c.newCase, 4, p);
		if (diag1) { // si on peut prendre un pion sur la diagonale 1
			casePlateau cPrise = p.cases[diag1];
			int x = cPrise.x - 1;
			int y = cPrise.y - 1;
			while (x > 0 && y > 0 && getCasePlateau(x, y, p).isLibre) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp = c;
				cp.prises[cp.nombre_prises] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.nombre_prises++;
				cp.chemin[cp.nombre_prises] = newCase;
				cp.newCase = newCase.notation;
				res[cpt_res++] = cp;
				if (!(getPossibleCasePos(newCase.notation, 2, p) /* si il n'y a pas d'aures prises sur la diagonale, on ajoute le coup */
				|| getPossibleCasePos(newCase.notation, 3, p))) {
					p_futur = p;
					plateau_prendre_pion(cPrise.notation, &p_futur);
					plateau_deplacer_pion(c.newCase,
							newCase.notation, &p_futur);
					coup * coups_completes =
							completerCoupDame(cp, 1, p_futur);
					int nbCoups = nombre_coups(coups_completes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						res[cpt_res++] = coups_completes[i];
					}
				}
				x--;
				y--;
			}
		}
		if (diag4) { // si on peut prendre un pion sur la diagonale 3
			casePlateau cPrise = p.cases[diag4];
			int x = cPrise.x + 1;
			int y = cPrise.y + 1;
			while (x <= 10 && y <= 10 && getCasePlateau(x, y, p).isLibre) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp = c;
				cp.prises[cp.nombre_prises] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.nombre_prises++;
				cp.chemin[cp.nombre_prises] = newCase;
				cp.newCase = newCase.notation;
				res[cpt_res++] = cp;
				if (!(getPossibleCasePos(newCase.notation, 2, p) /* si il n'y a pas d'aures prises sur la diagonale, on ajoute le coup */
				|| getPossibleCasePos(newCase.notation, 3, p))) {
					p_futur = p;
					plateau_prendre_pion(cPrise.notation, &p_futur);
					plateau_deplacer_pion(c.newCase,
							newCase.notation, &p_futur);
					coup * coups_completes =
							completerCoupDame(cp, 4, p_futur);
					int nbCoups = nombre_coups(coups_completes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						res[cpt_res++] = coups_completes[i];
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

	coup * cps = calloc(NBCOUPS, sizeof(coup));
	plateau p_futur = p;
	int nbCoup = 0;
	casePlateau case_courant = c;
	couleur_pion adversaire = (c.pion.couleur == blanc) ? noir : blanc;
	type_coup prise = x;

	/* conditions de départ */
	coup coup_courant;
	coup_courant.oldCase = case_courant.notation;
	coup_courant.nombre_prises = 0;
	coup_courant.tc = x;
	coup_courant.chemin[coup_courant.nombre_prises++] = case_courant;

	/* pour signaler qu'on est dans une rafle */
	int nouvelle_rafle = 0;
	int derniere_recherche_faite = 0; /* lorsqu'on revient sur la case de départ, on fait une derniere recherche */
	int fini = 0;
	int derniere_position = 0;

	/* quand on est sur la case de départ on marque l'element qu'on va visiter
	 * ainsi on ne reparcours pas une deuxieme fois quand on revient durant le backtrack
	 */
	casePlateau to_avoid[5];
	int cnt_avoid = 0;



	while (!fini) {
		/* ---------------------- Diagonale 1 ----------------------------- */
		int case_prise = getPossibleCasePos(c.notation, 1, p);
		casePlateau case_derriere = getCasePlateau(
				p.cases[case_prise].x - 1, p.cases[case_prise].y - 1, p);
		if (!case_prise || !case_derriere.isLibre
				|| case_derriere.notation == 0) { /* si la diagonale est vide, ou qu'on ne peut pas prendre le pion */
			int x = c.x - 1;
			int y = c.y - 1;
			while (x > 0 && y > 0 && getCasePlateau(x, y, p).isLibre) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pion. */
				casePlateau newCase = getCasePlateau(x, y, p);
				if (newCase.notation != 0) {
					coup cp;
					cp.tc = '-';
					cp.oldCase = c.notation;
					cp.nombre_prises = 0;
					cp.newCase = newCase.notation;
					cps[nbCoup++] = cp; /* on ajoute tous les coups à la liste */
				}
				x--;
				y--;
			}

		} else { /* sinon, il y a un pion à prendre sur la diagonale */
			casePlateau cPrise = p.cases[case_prise];
			int x = cPrise.x - 1;
			int y = cPrise.y - 1;
			while (x > 0 && y > 0 && getCasePlateau(x, y, p).isLibre) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp;
				cp.tc = prise;
				cp.oldCase = c.notation;
				cp.nombre_prises = 1;
				cp.prises[0] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.chemin[0] = c;
				cp.chemin[1] = newCase;
				cp.newCase = newCase.notation;

				p_futur = p;
				plateau_prendre_pion(cPrise.notation, &p_futur);
				plateau_deplacer_pion(c.notation,
						newCase.notation, &p_futur);

				cps[nbCoup++] = cp;

				if (getPossibleCasePos(newCase.notation, 2,
						p_futur) || getPossibleCasePos(
						newCase.notation, 3, p_futur)) { /* si il y a une prise possible sur la diagonale, on l'ajoute à la liste */
					coup * coups_completes =
							completerCoupDame(cp, 1, p_futur);

					int nbCoups = nombre_coups(coups_completes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						cps[nbCoup++] = coups_completes[i];
					}
					free(coups_completes);
				}
				x--;
				y--;
			}
		}

		/* ---------------------- Diagonale 2 ----------------------------- */

		case_prise = getPossibleCasePos(c.notation, 2, p);
		case_derriere = getCasePlateau(p.cases[case_prise].x + 1,
				p.cases[case_prise].y - 1, p);
		if (!case_prise || !case_derriere.isLibre
				|| case_derriere.notation == 0) { /* si la diagonale est vide */
			int x = c.x + 1;
			int y = c.y - 1;
			while (x <= 10 && y > 0 && getCasePlateau(x, y, p).isLibre) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pion. */
				casePlateau newCase = getCasePlateau(x, y, p);
				if (newCase.notation != 0) {
					coup cp;
					cp.tc = '-';
					cp.oldCase = c.notation;
					cp.nombre_prises = 0;
					cp.newCase = newCase.notation;
					cps[nbCoup++] = cp; /* on ajoute tous les coups à la liste */
				}
				x++;
				y--;
			}

		} else { /* sinon, il y a un pion à prendre sur la diagonale */
			casePlateau cPrise = p.cases[case_prise];
			int x = cPrise.x + 1;
			int y = cPrise.y - 1;
			while (x <= 10 && y > 0 && getCasePlateau(x, y, p).isLibre) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp;
				cp.tc = prise;
				cp.oldCase = c.notation;
				cp.nombre_prises = 1;
				cp.prises[0] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.chemin[0] = c;
				cp.chemin[1] = newCase;
				cp.newCase = newCase.notation;

				p_futur = p;
				plateau_prendre_pion(cPrise.notation, &p_futur);
				plateau_deplacer_pion(c.notation,
						newCase.notation, &p_futur);
				cps[nbCoup++] = cp;

				if (getPossibleCasePos(newCase.notation, 1,
						p_futur) || getPossibleCasePos(
						newCase.notation, 4, p_futur)) {

					coup * coups_completes =
							completerCoupDame(cp, 2, p_futur);

					int nbCoups = nombre_coups(coups_completes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						cps[nbCoup++] = coups_completes[i];
					}
					free(coups_completes);
				}
				x++;
				y--;
			}
		}

		/* ---------------------- Diagonale 3 ----------------------------- */

		case_prise = getPossibleCasePos(c.notation, 3, p);
		case_derriere = getCasePlateau(p.cases[case_prise].x - 1,
				p.cases[case_prise].y + 1, p);
		if (!case_prise || !case_derriere.isLibre
				|| case_derriere.notation == 0) { /* si la diagonale est vide */
			int x = c.x - 1;
			int y = c.y + 1;
			while (x > 0 && y <= 10 && getCasePlateau(x, y, p).isLibre) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pion. */
				casePlateau newCase = getCasePlateau(x, y, p);
				if (newCase.notation != 0) {
					coup cp;
					cp.tc = '-';
					cp.oldCase = c.notation;
					cp.nombre_prises = 0;
					cp.newCase = newCase.notation;
					cps[nbCoup++] = cp; /* on ajoute tous les coups à la liste */
				}
				x--;
				y++;
			}

		} else { /* sinon, il y a un pion à prendre sur la diagonale */
			casePlateau cPrise = p.cases[case_prise];
			int x = cPrise.x - 1;
			int y = cPrise.y + 1;
			while (x > 0 && y <= 10 && getCasePlateau(x, y, p).isLibre) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp;
				cp.tc = prise;
				cp.oldCase = c.notation;
				cp.nombre_prises = 1;
				cp.prises[0] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.chemin[0] = c;
				cp.chemin[1] = newCase;
				cp.newCase = newCase.notation;

				p_futur = p;
				plateau_prendre_pion(cPrise.notation, &p_futur);
				plateau_deplacer_pion(c.notation,
						newCase.notation, &p_futur);
				cps[nbCoup++] = cp;

				if (getPossibleCasePos(newCase.notation, 1,
						p_futur) || getPossibleCasePos(
						newCase.notation, 4, p_futur)) {
					coup * coups_completes =
							completerCoupDame(cp, 3, p_futur);

					int nbCoups = nombre_coups(coups_completes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						cps[nbCoup++] = coups_completes[i];
					}
					free(coups_completes);
				}
				x--;
				y++;
			}
		}

		/* ---------------------- Diagonale 4 ----------------------------- */

		case_prise = getPossibleCasePos(c.notation, 4, p);
		case_derriere = getCasePlateau(p.cases[case_prise].x + 1,
				p.cases[case_prise].y + 1, p);
		if (!case_prise || !case_derriere.isLibre
				|| case_derriere.notation == 0) { /* si la diagonale est vide */
			int x = c.x + 1;
			int y = c.y + 1;
			while (x <= 10 && y <= 10 && getCasePlateau(x, y, p).isLibre) { /* on parcours la diagonale jusqu'au bout ou jusqu'a rencontrer un autre pion. */
				casePlateau newCase = getCasePlateau(x, y, p);
				if (newCase.notation != 0) {
					coup cp;
					cp.tc = '-';
					cp.oldCase = c.notation;
					cp.nombre_prises = 0;
					cp.newCase = newCase.notation;
					cps[nbCoup++] = cp; /* on ajoute tous les coups à la liste */
				}
				x++;
				y++;
			}

		} else { /* sinon, il y a un pion à prendre sur la diagonale */
			casePlateau cPrise = p.cases[case_prise];
			int x = cPrise.x + 1;
			int y = cPrise.y + 1;
			while (x <= 10 && y <= 10 && getCasePlateau(x, y, p).isLibre) { /* dans ce cas, on parcours les cases de la diagonale derrière la prise */
				coup cp;
				cp.tc = prise;
				cp.oldCase = c.notation;
				cp.nombre_prises = 1;
				cp.prises[0] = cPrise;
				casePlateau newCase = getCasePlateau(x, y, p);
				cp.chemin[0] = c;
				cp.chemin[1] = newCase;
				cp.newCase = newCase.notation;

				p_futur = p;
				plateau_prendre_pion(cPrise.notation, &p_futur);
				plateau_deplacer_pion(c.notation,
						newCase.notation, &p_futur);
				cps[nbCoup++] = cp;

				if (getPossibleCasePos(newCase.notation, 2,
						p_futur) || getPossibleCasePos(
						newCase.notation, 3, p_futur)) { /* si il y a d'aures prises sur la diagonale */
					coup * coups_completes =
							completerCoupDame(cp, 4, p_futur);

					int nbCoups = nombre_coups(coups_completes);
					int i;
					for (i = 0; i < nbCoups; i++) {
						cps[nbCoup++] = coups_completes[i];
					}
					free(coups_completes);
				}
				x++;
				y++;
			}
		}

		fini = 1;
	}

	//free(deplacements);

	/* pour marquer la fin de tableau */
	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	cps[nbCoup++] = foo;
	return cps;
}






//coup* getCoupsPossiblesJoueur(const joueur j, const plateau board){}

coup* getCoups(const joueur j, const plateau p) {

	//coup cp[500];
	coup *cp = calloc(500, sizeof(coup));

	casePlateau c;
	int nbCoup = 0;
	int i;
	int k = 0;
	/* j'itere sur toutes les cases du plateau */
	for (i = 1; i < 51; i++) {
		c = p.cases[i];
		/* si dans cette case y'a un pion du joueur j
		 * on recupere tout les coups possibles de ce pion
		 */
		if ((!c.isLibre) && (c.pion.couleur == j.couleur)) {
			coup * aAjouter;
			if (c.pion.isDame) {
				aAjouter = coupsPossiblesDames(c, p);
			} else {
				aAjouter = coupsPossiblesPion(c, p);
			}
			/* recopie les coups possibles de ce pion dans cp */
			while ((aAjouter[k].oldCase != 0) && (aAjouter[k].newCase != 0)) {
				cp[nbCoup++] = aAjouter[k++];
			}
			k = 0;
		}
	}
	/* pour marquer la fin de tableau */
	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	cp[nbCoup++] = foo;

	coup *result = calloc(nbCoup, sizeof(coup));
	memcpy(&result, &cp, sizeof result);

	return result;
}

/* retourne les coups max du tableau en entrée */
coup* getCoupsMax(const coup *cp) {

	int i = 0;
	//coup coups_max[NBCOUPS];
	coup *coups_max = calloc(NBCOUPS, sizeof(coup));
	int nbCoupsMax = 0;
	int nbPrisesMax = 0;

	/* je parcours une premiere fois cp pour trouver le nb de prises max rencontré */
	while ((cp[i].oldCase != 0) && (cp[i].newCase != 0)) {
		if (cp[i].nbPrises > nbPrisesMax) {
			nbPrisesMax = cp[i].nbPrises;
		}
		i++;
	}

	/* je reparcours cp, cette fois je ne prend que les coups qui ont un
	 * nb de prises égal au nbPrisesMax
	 */
	i = 0;
	while ((cp[i].oldCase != 0) && (cp[i].newCase != 0)) {
		if (cp[i].nbPrises == nbPrisesMax) {
			coups_max[nbCoupsMax++] = cp[i];
		}
		i++;
	}

	/* je marque la fin de tableau */
	coup foo;
	foo.oldCase = 0;
	foo.newCase = 0;
	coups_max[nbCoupsMax++] = foo;

	coup *result = calloc(nbCoupsMax, sizeof(coup));
	memcpy(&result, &coups_max, sizeof(result));

	return result;
}

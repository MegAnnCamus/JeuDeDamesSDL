#include"plateau.h"

extern plateau plateauDeJeu;

plateau initPlateau(joueur j1, joueur j2){

	int i = 1;
	int x= 2;
	int y= 1;
	casePlateau caseBlanche = {.x = 0,.y = 0,.couleur = BLANC,.isLibre = TRUE,.notation = 0,.isHighlighted = FALSE};

	//Initialisation tour des joueurs
    j1.couleur = BLANC;
	j2.couleur = NOIR;

	plateau board;
	board.j1 = j1;
	board.j2 = j2;
	board.tour = j1;

	board.cases[0] = caseBlanche;

	while (i <= 50) {
		pion pion;
		pion.isDame = FALSE;

		casePlateau c;
		c.notation = i;
		c.couleur = NOIR;
		c.isHighlighted = FALSE;
		c.x = x;
		c.y = y;

		if (i <= 20) { //Côté noir : haut du plateau
			c.isLibre = FALSE;
			pion.couleur = NOIR;
			pion.isHighlighted = FALSE;
			c.pion = pion;
		} else if (i > 30) { //Côté blanc : bas du plateau
			c.isLibre = FALSE;
			pion.couleur = BLANC;
			pion.isHighlighted = FALSE;
			c.pion = pion;
		} else {
			c.isLibre = TRUE;
		}

		board.cases[i] = c;
		i++;

		//changement de case
		x = x + 2;
		if (i % 10 == 6) {
			x = 1;
			y++;
		} else if (i % 10 == 1) {
			x = 2;
			y++;
		}
	}

	return board;

}

casePlateau getCasePlateau(int x, int y, plateau board) {
	if (x < 1 || x > 10 || y < 1 || y > 10) {
		fprintf(stderr, "Case hors plateau (%i,%i)\n", x, y);
		return board.cases[0];
	}
	//Clic sur case blanche
	if ((x % 2) == (y % 2)) {
		return board.cases[0];
	}
	else
    {
		for (int i = 1; i <= 50; i++) {
			casePlateau c = board.cases[i];
			if (c.x == x && c.y == y) {
				return c;
			}
		}
		return board.cases[0];
	}
}

void miseAjour(coup coupJoueur, plateau *board) {
	casePlateau *cases = board->cases;
	if((cases[coupJoueur.oldCase].isLibre==TRUE) || (cases[coupJoueur.newCase].isLibre==FALSE)) {
		fprintf(stderr, "Impossible de jouer le coup");
	}
	else
    {
		deplacerPion(coupJoueur.oldCase,coupJoueur.newCase,board);
        //Test prise
		if(coupJoueur.type == PRISE) {
			for(int i = 0; i < coupJoueur.nbPrises; i++) {
				prendrePion(coupJoueur.prises[i].notation,board);
			}
		}
        //Test dame
		if(board->cases[coupJoueur.newCase].pion.couleur == BLANC && coupJoueur.newCase <= 5) {
			board->cases[coupJoueur.newCase].pion.isDame = TRUE;
		} else if( board->cases[coupJoueur.newCase].pion.couleur == NOIR && coupJoueur.newCase >= 46 ) {
			board->cases[coupJoueur.newCase].pion.isDame = TRUE;
		}
        //Changement tour
		if(board->tour.couleur == board->j1.couleur) {
			board->tour = board->j2;
		} else {
			board->tour = board->j1;
		}
	}

}

int partieTerminee(plateau board){
    int trouve = FALSE;
    char couleur;
    //parcours du damier à la recherche de deux pions de couleur différente
    for(int i = 1; i <= 50; i++ ) {
        if(board.cases[i].isLibre == FALSE) {
            if(trouve == TRUE) {
                if(couleur != board.cases[i].pion.couleur) {
                    //On a trouvé deux pions de couleur différente
                    return 0;
                }
            } else {
                trouve = TRUE;
                couleur = board.cases[i].pion.couleur;
            }
        }
    }
    //Si blanc gagne : on retourne 'W' et donc 87
    //Si noir gagne : on retourne 'B' et donc 66
    return couleur;
}

int coupDansListe(casePlateau c, casePlateau *liste, int tailleListe) {
	int resultat = FALSE;
	for (int i = 0; i < tailleListe - 1; ++i) {
		if (liste[i].notation == c.notation) {
			fprintf(stdout,"La case %d est dans la liste.\n", c.notation);
			resultat = TRUE;
			break;
		}
	}
	return resultat;
}

int nombreCoupsDansListe(coup *liste){
    int cpt = 0;
	while ((liste->oldCase != 0) && (liste->newCase != 0)) {
		cpt++;
		liste++;
	}
	return cpt;
}

casePlateau highlightPionClic(int *tab){
	casePlateau c;
	c = getCasePlateau(tab[0], tab[1], plateauDeJeu);
	//On déselectionne tous les pions
	for(int i=1;i<=50;i++){
        if(i!=c.notation)
            plateauDeJeu.cases[i].pion.isHighlighted = FALSE;
    }
    //Si c'est bien le joueur en cours
	if(c.pion.couleur == plateauDeJeu.tour.couleur){
        if(plateauDeJeu.cases[c.notation].pion.isHighlighted == TRUE)
            plateauDeJeu.cases[c.notation].pion.isHighlighted = FALSE;
        else
            plateauDeJeu.cases[c.notation].pion.isHighlighted = TRUE;
	}
	return c;
}

void highlightCase(int c, plateau* board){
	for(int i=1;i<=50;i++){
        if(i==c)
            board->cases[i].isHighlighted = TRUE;
    }
}

void resetHighlight(plateau* board){
    for(int i=1;i<=50;i++){
        board->cases[i].isHighlighted = FALSE;
    }
}

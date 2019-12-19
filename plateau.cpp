#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include"deplacement.h"

plateau initPlateau(joueur j1, joueur j2){

	int i = 1, x= 2, y= 1;
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
		c.x = x;c.y = y;

		if (i <= 20) { //Côté noir : haut du plateau
			c.isLibre = 0;
			pion.couleur = NOIR;
			pion.isHighlighted = FALSE;
			c.pion = pion;
		} else if (i > 30) { //Côté blanc : bas du plateau
			c.isLibre = 0;
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

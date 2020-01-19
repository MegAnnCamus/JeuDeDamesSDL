#include "moteur.h"

//pour savoir si un joueur est en train de r�aliser une action
int coupEnCoursMain = FALSE;
//liste des coups possibles
coup* coupsPossiblesMain;
//case de d�part d'une rafle
int caseDepartMain;
//pour v�rifier si on clique sur le m�me pion que l'on vient de d�placer
int caseIntermediaireMain;
//profondeur de l'alogirthme MinMax
int difficulte = 1;

int jouerCoup(int depart, int arrivee) {
	resetHighlight(&plateauDeJeu);
	if (coupEnCoursMain == TRUE) { //si le joueur est en train de faire une rafle
		if (depart == caseIntermediaireMain) { //si on d�place toujours le m�me pion
			int i = 0;
			coup c;
			while ((c = coupsPossiblesMain[i]).oldCase != 0) { //parcours du tableau des coups possibles
				if (c.oldCase == caseDepartMain) { //coups possibles depuis la case de d�part du coup � la recherche de celui que l'on est en train de r�aliser
					if (c.newCase == arrivee) { //si la case cliqu�e correspond � une case de fin de la rafle en cours
					    //mise � jour du plateau
						deplacerPion(depart, caseDepartMain, &plateauDeJeu);
						miseAjour(c, &plateauDeJeu);
						coupEnCoursMain = FALSE; //on a fini de jouer
						return 1;
					} else { //sinon on recherche si le d�placement fait partie d'une rafle
						int j = 0;
						casePlateau caseChemin;
						int nbPrisesLocal = c.nbPrises;
						while (j < nbPrisesLocal) {
							caseChemin = c.historiqueCases[j];
							if (caseChemin.notation == arrivee) { //on stocke la case sur laquelle on arrive dans l'historique des cases visit�es
								coupEnCoursMain = TRUE; //le coup est toujours en cours
								caseIntermediaireMain = arrivee; //mise � jour de la case interm�diaire de la rafle
								deplacerPion(depart, arrivee, &plateauDeJeu); //deplacement
								return 2;
							}
							j++;
						}
					}
				}
				i++;
			}
		} //partie coup invalide
		coupEnCoursMain = FALSE;
		caseDepartMain = 0;
		caseIntermediaireMain = 0;
		deplacerPion(depart, caseDepartMain, &plateauDeJeu);
		return 0;
	} else { //si on commence un nouveau tour
		int i = 0;
		coup c;
		int nbCoupsLocal = nombreCoupsDansListe(coupsPossiblesMain);
		while (i < nbCoupsLocal) { //parcours du tableau � la recherche de la case cliqu�e
			c = coupsPossiblesMain[i];
			if (c.oldCase == depart) { //si case trouv�e
				if (c.newCase == arrivee) { //test si c'est un coup complet
					miseAjour(c, &plateauDeJeu); //mise � jour du plateau
					return 1;
				} else { //si le mouvement fait partie d'une rafle
					int j = 0;
					casePlateau caseChemin;
					int nbPrisesLocal = c.nbPrises;
					while (j < nbPrisesLocal) {
						caseChemin = c.historiqueCases[j];
						if (caseChemin.notation == arrivee) {
							caseDepartMain = depart; //stockage case de d�part
							coupEnCoursMain = TRUE; //une rafle est en cours
							caseIntermediaireMain = arrivee; //mise � jour de la case interm�diaire
							deplacerPion(depart, arrivee, &plateauDeJeu); //d�placement
							return 2;
						}
						j++;
					}
				}
			}
			i++;
		}
		return 0; //coup non valide
	}
}

int jouerCoupCoordonnees(int x1, int y1, int x2, int y2) {
	casePlateau c1 = getCasePlateau(x1, y1, plateauDeJeu);
	casePlateau c2 = getCasePlateau(x2, y2, plateauDeJeu);
	return jouerCoup(c1.notation, c2.notation);
}

int showDeplacementsPossiblesCoordonnees(int x, int y) {
	casePlateau c = getCasePlateau(x, y, plateauDeJeu);
	return showDeplacementsPossibles(c.notation);
}

int showDeplacementsPossibles(int c) {
	resetHighlight(&plateauDeJeu);
	int res = 0;
	int i = 0;
	int n = nombreCoupsDansListe(coupsPossiblesMain);
	int currentCase = c;
	if (coupEnCoursMain == TRUE) {
		c = caseDepartMain;
	}
	int currentCaseTrouvee = 0;
	for (i = 0; i < n; i++) { //parcours de tous les coups
		coup cp = coupsPossiblesMain[i];
		if (cp.oldCase == c) { //si la case de d�part du coup correspond � celle cliqu�e
			casePlateau *cases = cp.historiqueCases; //cases par lesquelles on passe
			int nbCasesLocal = cp.nbPrises;
			int j = 0;
			while (j < nbCasesLocal) { //highlight les cases par lesquelles passe le coup
				casePlateau highlightedCase = cases[j];
				if (currentCaseTrouvee)
					highlightCase(highlightedCase.notation, &plateauDeJeu);
				if (highlightedCase.notation == currentCase)
					currentCaseTrouvee = 1;
				j++;
			}
			highlightCase(cp.newCase, &plateauDeJeu);
			res = 1;
		}
	}
	return res;
}

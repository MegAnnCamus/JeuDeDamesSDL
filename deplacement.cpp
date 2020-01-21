#include"deplacement.h"


//Test les conditions de base de déplacement des pions
int deplacerPion(int oldPosition, int newPosition, plateau *board) {
    //Deplacement impossible
	if ((oldPosition < 1) || (oldPosition > 50) || (newPosition < 1)
			|| (newPosition > 50) || (board->cases[oldPosition].isLibre==TRUE)
			|| (board->cases[newPosition].isLibre==FALSE)) {
		return 0;
	}
	else
    {
		//Pion que l'on déplace
		pion pion = board->cases[oldPosition].pion;
        //Mise à jour : la case où était le pion précédemment devient libre
        //La case sur laquelle on se déplace n'est plus libre et contient le pion déplacé
		board->cases[oldPosition].isLibre = TRUE;
		board->cases[newPosition].isLibre = FALSE;
		board->cases[newPosition].pion = pion;
		return 1;
	}
}

//Fonction de base de prise des pions
int prendrePion(int position, plateau *board) {
	if ((position < 1) || (position > 50) || (board->cases[position].isLibre==TRUE)) {
		return 0;
	} else {
	    //La case où est le pion que l'on prend devient libre
		board->cases[position].isLibre = TRUE;
		return 1;
	}
}


//Vérifications de base de prise des pions
int isPrenable(int position, plateau *board){
    if ((position < 1) || (position > 50) || (board->cases[position].isLibre==TRUE)) {
		return FALSE;
	} else {
		return TRUE;
	}
}

//brief Impl�mentation du min-max

#define MINIMUM -1
#define MAXIMUM 1

#include "fonctionEvaluation.h"

//brief Renvoie le meilleur coup que peut jouer le joueur courant.
//param profondeur La profondeur � laquelle on doit utiliser la fonction d'�valuation. (profondeur > 0)

coup jouerIA(const plateau p, int profondeur);

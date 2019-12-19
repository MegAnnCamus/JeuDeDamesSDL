typedef struct pion{
	char couleur;
	int isDame;
	int isHighlighted;
} pion;

typedef struct casePlateau{
	char couleur;
	int isLibre;	/*!< Vrai si la case est vide */
	pion pion;
	int nLig;
	int nCol;
	int notationOff;
	int isHighlighted; /*!< Si la case doit être affichée en surbrillance. */
} casePlateau;


#include <stdio.h>
#include <stdlib.h>
#include "min-max.h"

/** Le plateau de jeu qui sera utilis� tout au long de la partie. (Ne pas utiliser en dehors de moteur.c, utilisez ::get_plateau()) */
plateau p_jeu;


//Initialise une nouvelle partie, par d�faut une partie 2 joueurs
//le joueur pourra ensuite �tre pilot� par l'IA en changeant son type gr�ce � la fonction ::set_joueur_est_humain.

void initialiser_partie();


//Change le type humain ou IA du joueur.
//param couleur La couleur du joueur pour lequel on doit changer le type.
//param boolean Vrai si le joueur est humain, faux sinon.

void set_joueur_est_humain(couleur_pion couleur, int boolean);


//Renvoie le plateau de la partie pour le consulter.

plateau get_plateau();


//Sauvegarde l'�tat courant de la partie.
//return Vrai si la sauvegarde s'est bien effectu�e, faux si un probl�me est survenu.

int sauvegarder_partie(char * filename);


//Charge une partie depuis le disque.
//Vrai si le chargement s'est bien d�roul�, faux sinon.

int charger_partie(char * filename);


//Joue le coup pour le joueur courant.
//0 si le coup est invalide.
//1 si le coup est valide et termin�.
//2 si le mouvement fait partie d'un coup valide, on attend que le joueur termine son coup par un nouvel appel � cette fonction ::jouer_coup.

int jouer_coup(int depart, int arrivee);


//Identique � ::jouer_coup(int depart, int arrivee) mais prends les coordonn�es (x,y) de la case.

int jouer_coup_xy(int x1, int y1, int x2, int y2);


//Fait jouer un tour � l'IA.

void jouer_tour_ia();


//Joue sur la profondeur d'�valuation du min-max.

void set_difficulte(int i);


//D�bute un nouveau tour de jeu, fait jouer l'IA si c'est � elle de jouer, attend un coup humain sinon.
//return Faux si on attend q'un humain joue, vrai si l'IA � jou� et qu'on doit relancer imm�diatement un nouveau tour.

int commencer_tour();


//Met en surbrillance les pions qui permettent un d�placement valide pour ce tour.

void hint_pions_jouables();


//Met en surbrillance les d�placements possibles partant d'une case donn�e.
//param c Notation officielle de la case de d�part.

int hint_deplacements_possibles(int c);


//Identique � ::hint_deplacements_possibles(int c) mais prends les coordonn�es (x,y) de la case.

int hint_deplacements_possibles_xy(int x,int y);


//Met en surbrillance le meilleur coup � jouer en utilisant l'IA.

void hint_meilleur_coup();


//Renvoie Faux si la partie n'est pas termin�e, la couleur gagnante + 1 sinon.

int partie_terminee();

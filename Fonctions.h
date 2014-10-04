// D�claration des sous-programmes requis pour le programme principal 
// du jeu "Othello" du travail pratique (1) en KEE
//
// par Pierre Prud'homme, 2014
//------------------------------------------------------------------------------
#ifndef _FONCTIONS_H_
#define	_FONCTIONS_H_
#include "Othello.h"

// Fonction qui �crit � l'�cran qui a gagn� la partie !
void ConclurePartie(const Othello & jeu, ostream & out = cout);

// Fonction qui demande � l'utilisateur de lui fournir qui d�bute (les blancs ou les noirs)
Othello::Jetons IndiquerQuiDebute();

// Fonction qui joue le tour d'un jeton d'une certaine couleur re�ue en intrant
void JouerTour(Othello::Jetons & jetonQuiJoue, Othello & jeu, ostream & out = cout);

// Fonction qui joue le jeton une fois qu'il est d�termin� qu'il peut jouer son tour
void JouerJeton(Othello::Jetons & jetonQuiJoue, Othello & jeu, ostream& out);

// Fonction qui lit la prochaine position que le joueur veut jouer sur la grille
void LirePositionAJouer(Othello::Jetons jetonQuiJoue,int &ligne, int &colonne);

// Fonction qui permet de faire une pause entre chaque �tape du jeu
void Wait();

#endif
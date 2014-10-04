// Implantation du programme principal qui met en place la 
// boucle de jeu pour le "Othello" du travail pratique (1)
// en KEE
//
// par Pierre Prud'homme, 2014
//------------------------------------------------------------------------------
#include "Fonctions.h"
#include "Othello.h"
#include <fstream>
using namespace std;

int main()
{
	Othello jeu;
	Othello::Jetons jetonQuiJoue;
	ofstream fichierTrace ("Partie.txt");

	jetonQuiJoue = IndiquerQuiDebute();
	while(! jeu.EstFini())
	{
		JouerTour(jetonQuiJoue, jeu, fichierTrace);
		Wait();
	}
	ConclurePartie(jeu, fichierTrace);
}


// Définition des sous-programmes requis pour le programme principal 
// du jeu "Othello" du travail pratique (1) en KEE
//
// par Pierre Prud'homme, 2014
//------------------------------------------------------------------------------
#include "Fonctions.h"
#include <string>
#include <iostream>

// Fonction qui écrit à l'écran qui a gagné la partie !
void ConclurePartie(const Othello & jeu, ostream & out)
{
	string message;
	Othello::Jetons gagnant = jeu.DeterminerGagnant();

	if (&out != &cout) out << jeu << endl << endl;  // pour avoir une trace dans un fichier au besoin
	cout << jeu << endl << endl;

	if (gagnant == Othello::Blanc)
		message = "Les BLANCS ont gagne la partie";
	else if (gagnant == Othello::Noir)
		message = "Les NOIRS ont gagne la partie";
	else
		message = "La partie est nulle !!";
	
	if (&out != &cout) out << message << endl;
	cout << message << endl;
	Wait();
}


// Ce sous-programme permet de lire la prochaine position que veut jouer celui
// dont c'est le tour
//----------------------------------------------------------------------------------------
Othello::Jetons IndiquerQuiDebute()
{
	const char BLANC = 'b';
	const char NOIR = 'n'; 
	char debute; 

	cout << "Qui debute la partie (" << BLANC 
		 << " pour les blancs et "
		 << NOIR << " pour les noirs) : ";
	cin >> debute;
	while (tolower(debute) != BLANC && tolower(debute) != NOIR)
	{
		cout << "     ... mauvaise reponse ..." << endl;
		cout << "Qui debute la partie (" << BLANC 
			<< " pour les blancs et "
			<< NOIR << " pour les noirs) : ";		
		cin >> debute;
	}

	cin.ignore(cin.rdbuf()->in_avail()); // pour vider le buffer
	if (tolower(debute) == BLANC) return Othello::Blanc;
	return Othello::Noir;
}

void JouerJeton(Othello::Jetons & jetonQuiJoue, Othello & jeu, ostream& out)
{
	int ligne, colonne; 
	
	LirePositionAJouer(jetonQuiJoue, ligne, colonne);
	if (&out != &cout)
	{
		out << "Le joueur joue la position [" << ligne
			<< ", " << colonne << "]..." << endl << endl;
	}
	try
	{
		jeu.Jouer(jetonQuiJoue, ligne, colonne);
		jetonQuiJoue = (Othello::Jetons)((int)(jetonQuiJoue + 1) % Othello::Vide);
	}
	catch (out_of_range &)
	{
		if (&out != &cout) out << "Cette position est hors de la grille... " << endl; 
		cout << "Cette position est hors de la grille... " << endl; 
	}
	catch (exception & e)
	{
		if (&out != &cout) out << e.what() << endl;
		cout << e.what() << endl;
	}
}

// Fonction qui joue le tour d'un jeton d'une certaine couleur reçue en intrant
void JouerTour(Othello::Jetons & jetonQuiJoue, Othello & jeu, ostream& out)
{
	if (&out != &cout) // on produit le résultat dans un fichier en plus de faire l'affichage écran
	{
		out << jeu 
			<< endl << "C'est au tour des "
			<< (jetonQuiJoue == Othello::Blanc ? "BLANCS" : "NOIRS")
			<< " a jouer ..." << endl;
	}
	cout << jeu 
		<< endl << "C'est au tour des "
		<< (jetonQuiJoue == Othello::Blanc ? "BLANCS" : "NOIRS")
		<< " a jouer ..." << endl;	
	
	if (jeu.PeutJouerSonCoup(jetonQuiJoue))
	{
		JouerJeton(jetonQuiJoue, jeu, out);
	}
	else
	{
		if (&out != &cout)
		{
			out << endl << "Aucune position ne peut etre jouee par ce type de jeton ..." << endl;
		}
		cout << endl << "Aucune position ne peut etre jouee par ce type de jeton ..." << endl;
		jetonQuiJoue = (Othello::Jetons)((int)(jetonQuiJoue + 1) % Othello::Vide);
	}
}

// Ce sous-programme permet de lire la prochaine position que veut jouer celui
// dont c'est le tour
//----------------------------------------------------------------------------------------
void LirePositionAJouer(Othello::Jetons jetonQuiJoue, int &ligne, int &colonne)
{
	cout << "Donnez la ligne : "; 
	cin >> ligne;
	cout << "Donnez la colonne : ";
	cin >> colonne;
	cin.ignore(cin.rdbuf()->in_avail()); // pour vider le buffer
}

// Ce sous-programme permet d'attendre entre les écrans de résultats
//----------------------------------------------------------------------------------------
void Wait()
{
	cout << endl <<  "Any key to continue..." << endl;
	cin.ignore(cin.rdbuf()->in_avail()+1);
	system("cls");
}

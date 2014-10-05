// D�finition de la classe Othello qui permet d'implanter la grille de 
// jeu pour le "Othello" du travail pratique (1) en KEE
// Vous devez compl�ter cette d�claration et la d�finition de la classe
//
// par Pierre Prud'homme, 2014
// compl�t� par <nom des �tudiants>, <date>
//------------------------------------------------------------------------------
#include "Othello.h"
#include <string>
#include <iostream>
using namespace std;


const int Othello::TAILLE_GRILLE_DEFAUT = 8;


Othello::Othello() :nbJetonsBlanc_(2),nbJetonsNoir_(2)
{ 
	m_.SetNbLignes(TAILLE_GRILLE_DEFAUT);
	m_.SetNbColonnes(TAILLE_GRILLE_DEFAUT);

	for (int i = 0; i < TAILLE_GRILLE_DEFAUT; ++i)
	{
		for (int j = 0; j < TAILLE_GRILLE_DEFAUT; ++j)
		{
			m_.at(i).at(j) = Othello::Vide;
		}
	}

	// Pour s'ajuster aux diverses tailles de grille
	// en cours de mise au point. Je sugg�re que vous mettiez
	// la constante � 4 durant la mise au point 
	int centreInf = TAILLE_GRILLE_DEFAUT / 2 - 1 ;
	int centreSup = TAILLE_GRILLE_DEFAUT / 2;
	
	m_.at(centreInf).at(centreInf) = Othello::Blanc;
	m_.at(centreSup).at(centreSup) = Othello::Blanc;

	m_.at(centreInf).at(centreSup) = Othello::Noir;
	m_.at(centreSup).at(centreInf) = Othello::Noir;
}

void Othello::Afficher(ostream & output) const 
{
	int i, j;
	int maxLignes   = m_.GetNbLignes();
	int maxColonnes = m_.GetNbColonnes();
	const char SEPARATEUR_COLONNE = char(179);
	const char SEPARATEUR_COLONNE_LIGNE_PLEINE = char(197);

	// ligne d'ent�te num�rot�e
	system("cls");
	AfficherEnTete(output, maxColonnes);

	// grille
	string ligneDeSeparation;
	string partie = "---";
	partie += SEPARATEUR_COLONNE_LIGNE_PLEINE;
	for (int w = 0; w < maxColonnes+1; ++w) { ligneDeSeparation += partie; }

	output << ligneDeSeparation << endl;
	for (i = 0; i < maxLignes; i++)
	{
		output.width(2);
		output << i << " " << SEPARATEUR_COLONNE;
		for (j = 0; j < maxColonnes; j++)
		{
			output << DeterminerChaine(i, j);
		}
		output << endl << ligneDeSeparation << endl;
	}
	output << endl;

	// Il reste � ajouter l'affichage du nombre de jetons blancs et de jetons noirs
	
	output << "Blancs : " << nbJetonsBlanc_;
	output.width(24);
	output << "Noirs : " << nbJetonsNoir_;
}

void Othello::AfficherEnTete(ostream & output, int maxColonnes) const
{
	output << "  ";
	for (int i = 0; i < maxColonnes; ++i)
	{
		output << "  ";
		output.width(2); output << i;
	}
	output << endl;
}

string Othello::DeterminerChaine(int i, int j) const
{
	string chaine;

	if (m_.at(i).at(j) == Othello::Vide)
		chaine = "   |";
	else
		if (m_.at(i).at(j) == Othello::Blanc)
			chaine = " B |";
		else
			chaine = " N |";
	return chaine;
}

void Othello::Jouer(Othello::Jetons jeton, int ligne, int colonne) throw(exception)
{
	// V�rifier si la position jou�e est d�j� occup�e par un autre jeton; si elle
	// est occup�e =>> exception


	// V�rifier que la position disponible est 'jouable', c'est � dire qu'on 
	// peut mettre le jeton � cette case en fonction des r�gles. Si on ne peut
	// y mettre le jeton =>> exception
	if ( ! EstPositionJouable(jeton, ligne, colonne))
		throw exception("Cette position ne peut etre jouee par ce type de jeton");

	// � ce stade, on sait que la position est jouable donc on met le jeton � cette position


	// puis on inverse les jetons entre cette position et toutes celles o� il y a un 
	// autre jeton de cette couleur et des voisines d'une couleur oppos�e

}

bool Othello::EstPositionJouable(Othello::Jetons jeton, int ligne, int colonne) const
{
	// clairement � modifier ;-)
	return true;
}

// indique si la partie est finie
bool Othello::EstFini() const
{
	// clairement � modifier ;-)
	return false;  
}

Othello::Jetons Othello::DeterminerGagnant() const
{
	// clairement � modifier ;-)
	return Othello::Vide;
}

bool Othello::PeutJouerSonCoup(Othello::Jetons jetonQuiJoue) const
{
	// clairement � modifier ;-)
	for (size_t i = 0; i < m_.GetNbLignes(); i++)
	{
		for (size_t y = 0; y < m_.GetNbColonnes()-1; y++)
		{
			if (m_[i][y] == Othello::Vide &&  m_[i][y])
			{
				//test
			}
		}
	}
	return false;
}


ostream& operator << (ostream & out, const Othello & jeu)
{
	jeu.Afficher(out);
	return out;
}
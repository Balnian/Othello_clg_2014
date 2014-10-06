// Définition de la classe Othello qui permet d'implanter la grille de 
// jeu pour le "Othello" du travail pratique (1) en KEE
// Vous devez compléter cette déclaration et la définition de la classe
//
// par Pierre Prud'homme, 2014
// complété par <nom des étudiants>, <date>
//------------------------------------------------------------------------------
#include "Othello.h"
#include <string>
#include <iostream>
using namespace std;



const int Othello::TAILLE_GRILLE_DEFAUT = 4;




Othello::Othello() :nbJetonsBlanc_(2),nbJetonsNoir_(2)
{ 
	m_.SetNbLignes(TAILLE_GRILLE_DEFAUT);
	m_.SetNbColonnes(TAILLE_GRILLE_DEFAUT);

	for (int i = 0; i < TAILLE_GRILLE_DEFAUT; ++i)
	{
		for (int j = 0; j < TAILLE_GRILLE_DEFAUT; ++j)
		{
			m_[i][j] = Othello::Vide;
		}
	}

	// Pour s'ajuster aux diverses tailles de grille
	// en cours de mise au point. Je suggère que vous mettiez
	// la constante à 4 durant la mise au point 
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

	// ligne d'entête numérotée
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

	// Il reste à ajouter l'affichage du nombre de jetons blancs et de jetons noirs
	
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
	// Vérifier si la position jouée est déjà occupée par un autre jeton; si elle
	// est occupée =>> exception
	if (m_[ligne][colonne] != Othello::Vide)
		throw exception("cette Position est deja occupee");


	// Vérifier que la position disponible est 'jouable', c'est à dire qu'on 
	// peut mettre le jeton à cette case en fonction des règles. Si on ne peut
	// y mettre le jeton =>> exception
	if ( ! EstPositionJouable(jeton, ligne, colonne))
		throw exception("Cette position ne peut etre jouee par ce type de jeton");

	// À ce stade, on sait que la position est jouable donc on met le jeton à cette position

	// puis on inverse les jetons entre cette position et toutes celles où il y a un 
	// autre jeton de cette couleur et des voisines d'une couleur opposée
	InverserJetons(jeton, ligne, colonne);

}

bool Othello::EstPositionJouable(Othello::Jetons jeton, int ligne, int colonne) const
{
	

	if (m_[ligne][colonne] == Vide)
	{
		//Vérifie le jeton a droite
		if (m_[ligne][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = colonne + 1; r < m_.GetNbColonnes(); r++)
			{
				if (m_[ligne][r] == jeton)				
					return true;
							
			}
		}

		//vérifie le jeton a gauche
		if (m_[ligne][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = colonne - 1; r >= 0; r--)
			{
				if (m_[ligne][r] == jeton)				
					return true;				
			}
		}

		//vérifie le jeton du haut
		if (m_[(ligne == 0) ? ligne : ligne - 1][colonne] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = ligne - 1; r >= 0; r--)
			{
				if (m_[r][colonne] == jeton)				
					return true;
			}
		}

		//vérifie le jeton du bas
		if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][colonne] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = ligne + 1; r < m_.GetNbLignes(); r++)
			{
				if (m_[r][colonne] == jeton)				
		     		return true;
				
			
			}
		}

		//vérifie le jeton en diagonale haut droite
		if (m_[(ligne == 0) ? ligne : ligne - 1][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = 1; ligne - r >= 0 && colonne + r<m_.GetNbColonnes(); r++)
			{
				if (m_[ligne - r][colonne + r] == jeton)				
					 return true;
				
				
			}
		}

		//vérifie le jeton en diagonale haut gauche
		if (m_[(ligne == 0) ? ligne : ligne - 1][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = 1; ligne - r >= 0 && colonne - r >= 0; r++)
			{
				if (m_[ligne - r][colonne - r] == jeton)				
					 return true;			
			}
		}

		//vérifie le jeton en diagonale bas gauche
		if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = 1; ligne + r <m_.GetNbLignes() && colonne - r >= 0; r++)
			{
				if (m_[ligne + r][colonne - r] == jeton)				
					return true;			
			}
		}

		//vérifie le jeton en diagonale bas droite
		if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = 1; ligne + r <m_.GetNbLignes() && colonne + r<m_.GetNbColonnes(); r++)
			{
				if (m_[ligne + r][colonne + r] == jeton)				
					return true;
				
				
			}
		}

	}
	return false;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//test de fred


//bool jouable = false;
//
//
//for (size_t i = 0; i< m_.GetNbLignes(); i++)
//	{
//		for (size_t j =0; j < m_.GetNbColonnes(); i++)
//		{
//			if (ligne + 1 < m_.GetNbLignes() - 1 && colonne + 1 < m_.GetNbColonnes() - 1)
//			{
//
//
//				/*if (m_[ligne][colonne + 1] != jeton && m_[ligne][colonne + 1] != Vide)
//					jouable = true;*/
//
//				//bas
//				/*if (m_[ligne - 1][colonne] != jeton && m_[ligne + 1][colonne] != Vide)
//					jouable = true;*/
//
//
//				if (m_[ligne][colonne - 1] != jeton && m_[ligne][colonne - 1] != Vide)
//					jouable = true;
//			}
//		}
//	}
//
// 
//  
//return jouable;

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// indique si la partie est finie
bool Othello::EstFini() const
{
	bool fin = true;

	for (size_t i = 0; i < m_.GetNbLignes(); i++)		
	{
		for (size_t j = 0; j < m_.GetNbColonnes(); j++)
		{
			if (m_[i][j] == Vide)
			   fin = false;
		}
	}
	 
	return fin;  
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
Othello::Jetons Othello::DeterminerGagnant() const
{
	return (nbJetonsBlanc_ > nbJetonsNoir_) ? Othello::Blanc : (nbJetonsNoir_ > nbJetonsBlanc_) ? Othello::Noir:Othello::Vide;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Othello::PeutJouerSonCoup(Othello::Jetons jetonQuiJoue) const
{
	// clairement à modifier ;-)


		for (int i = 0; i < m_.GetNbLignes(); i++)
		{
			for (int y = 0; y < m_.GetNbColonnes(); y++)

			{
				if (m_[i][y] == Vide)
				{
					//Vérifie le jeton a droite
					if (m_[i][(y == m_.GetNbColonnes() - 1) ? y : y + 1] == (jetonQuiJoue == Noir) ? Blanc : Noir)
					{
						for (int r = y + 1; r < m_.GetNbColonnes(); r++)
						{
							if (m_[i][r] == jetonQuiJoue)
							   return true;
														
						}
					}

					//vérifie le jeton a gauche
					if (m_[i][(y == 0) ? y : y - 1] == (jetonQuiJoue == Noir) ? Blanc : Noir)
					{
						for (int r = y - 1; r >= 0; r--)
						{
							if (m_[i][r] == jetonQuiJoue)							
							  return true;														
						}
					}

					//vérifie le jeton du haut
					if (m_[(i == 0) ? i : i - 1][y] == (jetonQuiJoue == Noir) ? Blanc : Noir)
					{
						for (int r = i - 1; r >= 0; r--)
						{
							if (m_[r][y] == jetonQuiJoue)
								return true;
							
						
						}
					}

					//vérifie le jeton du bas
					if (m_[(i == m_.GetNbLignes() - 1) ? i : i + 1][y] == (jetonQuiJoue == Noir) ? Blanc : Noir)
					{
						for (int r = i + 1; r < m_.GetNbLignes(); r++)
						{
							if (m_[r][y] == jetonQuiJoue)							
							   return true;
							
							
						}
					}

					//vérifie le jeton en diagonale haut droite
					if (m_[(i == 0) ? i : i - 1][(y == m_.GetNbColonnes() - 1) ? y : y + 1] == (jetonQuiJoue == Noir) ? Blanc : Noir)
					{
						for (int r = 1; i - r >= 0 && y + r < m_.GetNbColonnes(); r++)
						{
							if (m_[i - r][y + r] == jetonQuiJoue)
								return true;
							
							
						}
					}

					//vérifie le jeton en diagonale haut gauche
					if (m_[(i == 0) ? i : i - 1][(y == 0) ? y : y - 1] == (jetonQuiJoue == Noir) ? Blanc : Noir)
					{
						for (int r = 1; i - r >= 0 && y - r >= 0; r++)
						{
							if (m_[i - r][y - r] == jetonQuiJoue)							
								return true;
							
							
						}
					}

					//vérifie le jeton en diagonale bas gauche
					if (m_[(i == m_.GetNbLignes() - 1) ? i : i + 1][(y == 0) ? y : y - 1] == (jetonQuiJoue == Noir) ? Blanc : Noir)
					{
						for (int r = 1; i + r < m_.GetNbLignes() && y - r >= 0; r++)
						{
							if (m_[i + r][y - r] == jetonQuiJoue)							
								return true;
							
							
						}
					}

					//vérifie le jeton en diagonale bas droite
					if (m_[(i == m_.GetNbLignes() - 1) ? i : i + 1][(y == m_.GetNbColonnes() - 1) ? y : y + 1] == (jetonQuiJoue == Noir) ? Blanc : Noir)
					{
						for (int r = 1; i + r < m_.GetNbLignes() && y + r < m_.GetNbColonnes(); r++)
						{
							if (m_[i + r][y + r] == jetonQuiJoue)							
								return true;
							
							
						}
					}

				}
			}
		}
		return false;

}

void Othello::InverserJetons(Othello::Jetons jeton, int ligne, int colonne)
{
	if (m_[ligne][colonne] == Vide)
	{
		//Vérifie le jeton a droite
		if (m_[ligne][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = colonne + 1; r < m_.GetNbColonnes(); r++)
			{
				if (m_[ligne][r] == jeton)
				{
					for (int z = colonne; z < r; z++)
					{
						m_[ligne][z] = jeton;
						
					}
				}				
			}
		}

		//vérifie le jeton a gauche
		if (m_[ligne][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = colonne - 1; r >= 0; r--)
			{
				if (m_[ligne][r] == jeton)
				{
					for (int z = colonne; z >r; z--)
					{
						m_[ligne][z] = jeton;
						
					}
				}				
			}
		}

		//vérifie le jeton du haut
		if (m_[(ligne == 0) ? ligne : ligne - 1][colonne] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = ligne - 1; r >= 0; r--)
			{
				if (m_[r][colonne] == jeton)
				{
					for (int z = ligne; z >r; z--)
					{
						m_[z][colonne] = jeton;
						
					}
				}				
			}
		}

		//vérifie le jeton du bas
		if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][colonne] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = ligne + 1; r < m_.GetNbLignes(); r++)
			{
				if (m_[r][colonne] == jeton)
				{
					for (int z = ligne; z < r; z++)
					{
						m_[z][colonne] = jeton;
						
					}
				}				
			}
		}

		//vérifie le jeton en diagonale haut droite
		if (m_[(ligne == 0) ? ligne : ligne - 1][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = 1; ligne - r >= 0 && colonne + r<m_.GetNbColonnes(); r++)
			{
				if (m_[ligne - r][colonne + r] == jeton)
				{
					for (int z = 0; z < r; z++)
					{
						m_[ligne - z][colonne + z] = jeton;
						
					}
				}				
			}
		}

		//vérifie le jeton en diagonale haut gauche
		if (m_[(ligne == 0) ? ligne : ligne - 1][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = 1; ligne - r >= 0 && colonne - r >= 0; r++)
			{
				if (m_[ligne - r][colonne - r] == jeton)
				{
					for (int z = 0;  z < r; z++)
					{
						m_[ligne - z][colonne - z] = jeton;
						
					}
				}
			}
		}

		//vérifie le jeton en diagonale bas gauche
		if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = 1; ligne + r <m_.GetNbLignes() && colonne - r >= 0; r++)
			{
				if (m_[ligne + r][colonne - r] == jeton)
				{
					for (int z = 0; z < r; z++)
					{
						m_[ligne + z][colonne - z] = jeton;
						
					}
				}				
			}
		}

		//vérifie le jeton en diagonale bas droite
		if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
		{
			for (int r = 1; ligne + r <m_.GetNbLignes() && colonne + r<m_.GetNbColonnes(); r++)
			{
				if (m_[ligne + r][colonne + r] == jeton)
				{
					for (int z = 0; z<r; z++)
					{
						m_[ligne + z][colonne + z] = jeton;
						
					}
				}				
			}
		}

	}
	CalculDuNbDeJeton();

}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void Othello::CalculDuNbDeJeton()
{

	nbJetonsBlanc_ = 0;
	nbJetonsNoir_ = 0;

	for (size_t i = 0; i < m_.GetNbLignes(); i++)
	{
		for (size_t j = 0; j < m_.GetNbColonnes(); j++)
		{
			if (m_[i][j] == Othello::Noir)		
				nbJetonsNoir_++;
			

			if (m_[i][j] == Othello::Blanc)

				nbJetonsBlanc_++;
		}
	}


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
ostream& operator << (ostream & out, const Othello & jeu)
{
	jeu.Afficher(out);
	return out;
}
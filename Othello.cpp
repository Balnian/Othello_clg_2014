// Définition de la classe Othello qui permet d'implanter la grille de 
// jeu pour le "Othello" du travail pratique (1) en KEE
// Vous devez compléter cette déclaration et la définition de la classe
//
// par Pierre Prud'homme, 2014
// complété par <Francis Lemaire && Frédéric Paquette>, <2014-10-06>
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
///////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Othello::Jouer(Othello::Jetons jeton, int ligne, int colonne) throw(exception)
{
	 //verifie si la position passer est valide
	if (!(ligne < m_.GetNbLignes() && colonne < m_.GetNbColonnes() && ligne >= 0 && colonne >= 0))
		throw exception("position invalide");
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
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Othello::EstPositionJouable(Othello::Jetons jeton, int ligne, int colonne) const
{
	
   bool verification = false;


   //Vérifie le jeton a droite
   if (m_[ligne][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
      verification |= Verif(jeton, ligne, colonne, Othello::Plus, Othello::Zero).Validiter;
   //vérifie le jeton a gauche
   if (m_[ligne][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
      verification |= Verif(jeton, ligne, colonne, Othello::Moins, Othello::Zero).Validiter;
   //vérifie le jeton du haut
   if (m_[(ligne == 0) ? ligne : ligne - 1][colonne] == (jeton == Noir) ? Blanc : Noir)
      verification |= Verif(jeton, ligne, colonne, Othello::Zero, Othello::Moins).Validiter;
   //vérifie le jeton du bas
   if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][colonne] == (jeton == Noir) ? Blanc : Noir)
      verification |= Verif(jeton, ligne, colonne, Othello::Zero, Othello::Plus).Validiter;
   //vérifie le jeton en diagonale haut droite
   if (m_[(ligne == 0) ? ligne : ligne - 1][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
      verification |= Verif(jeton, ligne, colonne, Othello::Plus, Othello::Moins).Validiter;
   //vérifie le jeton en diagonale haut gauche
   if (m_[(ligne == 0) ? ligne : ligne - 1][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
      verification |= Verif(jeton, ligne, colonne, Othello::Moins, Othello::Moins).Validiter;
   //vérifie le jeton en diagonale bas gauche
   if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
      verification |= Verif(jeton, ligne, colonne, Othello::Moins, Othello::Plus).Validiter;
   //vérifie le jeton en diagonale bas droite
   if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
      verification |= Verif(jeton, ligne, colonne, Othello::Plus, Othello::Plus).Validiter;
   return verification;


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Othello::PosValid Othello::Verif(Othello::Jetons jeton, int ligne, int colonne, Orientation X, Orientation Y) const
{
	 //verifie la direction en fonction de loriantation passer en parametre
   for (int r = 1; ligne + (r*Y) <m_.GetNbLignes() && colonne + (r*X)<m_.GetNbColonnes() && ligne + (r*Y) >= 0 && colonne + (r*X)>=0; r++)
   {
      if (m_[ligne + (r*Y)][colonne + (r*X)] == jeton)
         return PosValid(true, colonne + (r*X), ligne + (r*Y));
      if (m_[ligne + (r*Y)][colonne + (r*X)] == Vide)
         return PosValid(false, colonne + (r*X), ligne + (r*Y));
   }
   return PosValid(false, colonne, ligne);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// indique si la partie est finie
bool Othello::EstFini() const
{
	return !PeutJouerSonCoup(Noir) && !PeutJouerSonCoup(Blanc);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
Othello::Jetons Othello::DeterminerGagnant() const
{
	//verifie quelle jetons en a le plus sur le board et le retourne si le nombre est == retourne vide
	return (nbJetonsBlanc_ > nbJetonsNoir_) ? Othello::Blanc : (nbJetonsNoir_ > nbJetonsBlanc_) ? Othello::Noir:Othello::Vide;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Othello::PeutJouerSonCoup(Othello::Jetons jetonQuiJoue) const
{
	//test toutes les cases vide et verifie si le jeton qui joue peut jouer son tour
   bool valide = false;

   for (int i = 0; i < m_.GetNbLignes(); i++)
   {
      for (int y = 0; y < m_.GetNbColonnes(); y++)
      {
		  if (m_[i][y]==Vide)
			  valide |= EstPositionJouable(jetonQuiJoue, i, y);
      }
   }
		return valide;

}

void Othello::InverserJetons(Othello::Jetons jeton, int ligne, int colonne)
{
   //Vérifie le jeton a droite
   if (m_[ligne][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
      FlipLigne(jeton, ligne, colonne, Othello::Plus, Othello::Zero);
   //vérifie le jeton a gauche
   if (m_[ligne][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
      FlipLigne(jeton, ligne, colonne, Othello::Moins, Othello::Zero);
   //vérifie le jeton du haut
   if (m_[(ligne == 0) ? ligne : ligne - 1][colonne] == (jeton == Noir) ? Blanc : Noir)
      FlipLigne(jeton, ligne, colonne, Othello::Zero, Othello::Moins);
   //vérifie le jeton du bas
   if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][colonne] == (jeton == Noir) ? Blanc : Noir)
      FlipLigne(jeton, ligne, colonne, Othello::Zero, Othello::Plus);
   //vérifie le jeton en diagonale haut droite
   if (m_[(ligne == 0) ? ligne : ligne - 1][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
      FlipLigne(jeton, ligne, colonne, Othello::Plus, Othello::Moins);
   //vérifie le jeton en diagonale haut gauche
   if (m_[(ligne == 0) ? ligne : ligne - 1][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
      FlipLigne(jeton, ligne, colonne, Othello::Moins, Othello::Moins);
   //vérifie le jeton en diagonale bas gauche
   if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][(colonne == 0) ? colonne : colonne - 1] == (jeton == Noir) ? Blanc : Noir)
      FlipLigne(jeton, ligne, colonne, Othello::Moins, Othello::Plus);
   //vérifie le jeton en diagonale bas droite
   if (m_[(ligne == m_.GetNbLignes() - 1) ? ligne : ligne + 1][(colonne == m_.GetNbColonnes() - 1) ? colonne : colonne + 1] == (jeton == Noir) ? Blanc : Noir)
      FlipLigne(jeton, ligne, colonne, Othello::Plus, Othello::Plus);
	CalculDuNbDeJeton();

}
void Othello::FlipLigne(Othello::Jetons jeton, int ligne, int colonne, Orientation X, Orientation Y)
{
	// appelle la fonction verif qui valid si la direction est valid si oui flip les jetons jusquau jeton de sa couleur
   Othello::PosValid data;
   if ((data = Verif(jeton, ligne, colonne, X, Y)).Validiter)
   {
      for (int r = 0; (Y<Zero) ? (ligne + (r*Y) > data.Pos.Y) :
                                 (Y>Zero) ? (ligne + (r*Y) < data.Pos.Y) :
                                             true 
                    &&(X<Zero) ? (colonne + (r*X) > data.Pos.X) :
                                 (X>Zero) ? (colonne + (r*X) < data.Pos.X) :
                                             true; r++)
      {     
         m_[ligne + (r*Y)][colonne + (r*X)] = jeton;
      }
   }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////
void Othello::CalculDuNbDeJeton()
{
	//calcul le nombre de jetons de chaque couleur sur le board
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
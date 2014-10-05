// D�claration de la classe Othello qui permet d'implanter la grille de 
// jeu pour le "Othello" du travail pratique (1) en KEE
// Vous devez compl�ter cette d�claration et la d�finition de la classe
//
// par Pierre Prud'homme, 2014
// compl�t� par <nom des �tudiants>, <date>
//------------------------------------------------------------------------------
#ifndef _OTHELLO_H_
#define _OTHELLO_H_
#pragma warning (disable : 4290)
#include "Matrice.h"
#include <iostream>
using namespace std;

class Othello
{
public:
	enum Jetons {Blanc, Noir, Vide};

private:
	static const int TAILLE_GRILLE_DEFAUT;
	Matrice <Jetons> m_;
	int nbJetonsBlanc_;
	int nbJetonsNoir_;
	
	// inverse les jetons par rapport � la position jouer
	void InverserJetons(Othello::Jetons jeton, int ligne, int colonne);

	//--- requise pour la m�thode publique Jouer
	bool   EstPositionJouable(Othello::Jetons jeton, int ligne, int colonne) const;

	//--- requises pour l'affichage
	void   AfficherEnTete(ostream & output, int maxColonnes) const;
	string DeterminerChaine(int i, int j) const;

public:
	Othello();
	void Afficher(ostream &) const;
	Othello::Jetons DeterminerGagnant() const;
	bool EstFini() const;
	void Jouer(Othello::Jetons jeton, int ligne, int colonne) throw(exception);
	bool PeutJouerSonCoup(Othello::Jetons jetonQuiJoue) const;
};

ostream& operator << (ostream & out, const Othello & jeu);

#endif
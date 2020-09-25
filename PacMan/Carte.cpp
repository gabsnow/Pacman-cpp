// Carte.cpp
// Fait par Gabriel Bourgeois le 23 Septembre 2017
// Définition des fonctions associés à un carte

#include "Carte.h"
#include <fstream>
#include <iostream>
using namespace std;

vector<string>LireCarte(ifstream& Carte)
{
	string MapLine;
	vector<string>PacMap;

	if (!Carte)
	{
		cout << "Le fichier n'a pas pu ouvrir." << endl;
		PacMap.push_back("-1");
	}
	else
	{
		while (getline(Carte, MapLine))
		{
			PacMap.push_back(MapLine);
		}
	}

	return PacMap;
}
bool CarteEstRectangulaire(const vector<string>& PacMap)
{
	bool Rectangulaire = true;

	for (int i = 1; i < PacMap.size() && Rectangulaire; i++)
	{
		Rectangulaire = PacMap[i - 1].size() == PacMap[i].size();
	}
	return Rectangulaire;
}
bool CaractereSontValides(const vector<string>& PacMap)
{
	bool Valid = true;
	short LineSize, MapSize = PacMap.size();

	for (int i = 0; i < MapSize && Valid; i++)
	{
		LineSize = PacMap[i].size();
		for (int j = 0; j < LineSize && Valid; j++)
		{
			Valid = PacMap[i][j] == Mur || PacMap[i][j] == PacMan || PacMap[i][j] == Pilule || PacMap[i][j] == Fantome ||
				PacMap[i][j] == Vide;
		}
	}
	return Valid;
}
short CalculerHauteurCarte(const vector<string>& PacMap)
{
	return PacMap.size();
}
short CalculerLargeurCarte(const vector<string>& PacMap)
{
	return PacMap[0].size();
}
void AfficherCarte(const vector<string>& PacMap)
{
	for (const auto& Line : PacMap)
	{
		cout << Line << endl;
	}
}
bool CarteEstValide(const std::vector<std::string>& PacMap)
{
	return PacMap[0] != "-1" && CarteEstRectangulaire(PacMap) && CaractereSontValides(PacMap);
}
void ActionPacMan(vector<string>& PacMap, char& TheAction)
{
	int Hauteur = CalculerHauteurCarte(PacMap);
	int Largeur = CalculerLargeurCarte(PacMap);
	bool PosPacMan = false;

	ActionMajuscules(TheAction);

	if (TheAction == Haut)
	{
		for (int i = 0; i < Hauteur && !PosPacMan; i++)
		{
			for (int j = 0; j < Largeur && !PosPacMan; j++)
			{
				PosPacMan = PacMap[i][j] == PacMan;
				if (PosPacMan)
				{
					if (i == 0)
					{
						if (PacMap[Hauteur - 1][j] != Mur)
						{
							PacMap[i][j] = Vide;
							PacMap[Hauteur - 1][j] = PacMan;
						}
					}
					else if (PacMap[i - 1][j] != Mur)
					{
						PacMap[i][j] = Vide;
						PacMap[i - 1][j] = PacMan;
					}
				}
			}
		}
	}
	else if (TheAction == Gauche)
	{
		for (int i = 0; i < Hauteur && !PosPacMan; i++)
		{
			for (int j = 0; j < Largeur && !PosPacMan; j++)
			{
				PosPacMan = PacMap[i][j] == PacMan;
				if (PosPacMan)
				{
					if (j == 0)
					{
						if (PacMap[i][Largeur - 1] != Mur)
						{
							PacMap[i][j] = Vide;
							PacMap[i][Largeur - 1] = PacMan;
						}
					}
					else if (PacMap[i][j - 1] != Mur)
					{
						PacMap[i][j] = Vide;
						PacMap[i][j - 1] = PacMan;
					}
				}
			}
		}
	}
	else if (TheAction == Bas)
	{
		for (int i = 0; i < Hauteur && !PosPacMan; i++)
		{
			for (int j = 0; j < Largeur && !PosPacMan; j++)
			{
				PosPacMan = PacMap[i][j] == PacMan;
				if (PosPacMan)
				{
					if (i == Hauteur - 1)
					{
						if (PacMap[0][j] != Mur)
						{
							PacMap[i][j] = Vide;
							PacMap[0][j] = PacMan;
						}
					}
					else if (PacMap[i + 1][j] != Mur)
					{
						PacMap[i][j] = Vide;
						PacMap[i + 1][j] = PacMan;
					}
				}
			}
		}
	}
	else if (TheAction == Droite)
	{
		for (int i = 0; i < Hauteur && !PosPacMan; i++)
		{
			for (int j = 0; j < Largeur && !PosPacMan; j++)
			{
				PosPacMan = PacMap[i][j] == PacMan;
				if (PosPacMan)
				{
					if (j == Largeur - 1)
					{
						if (PacMap[i][0] != Mur)
						{
							PacMap[i][j] = Vide;
							PacMap[i][0] = PacMan;
						}
					}
					else if (PacMap[i][j + 1] != Mur)
					{
						PacMap[i][j] = Vide;
						PacMap[i][j + 1] = PacMan;
					}
				}
			}
		}
	}
}
void ActionMajuscules(char& TheAction)
{
	if (TheAction == 'S')
		TheAction = Bas;
	else if (TheAction == 'W')
		TheAction = Haut;
	else if (TheAction == 'A')
		TheAction = Gauche;
	else if (TheAction == 'D')
		TheAction = Droite;
	else if (TheAction == 'Q')
		TheAction = Quitter;
}

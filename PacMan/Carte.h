#ifndef CARTE_H
#define CARTE_H
// Carte.h
// Fait par Gabriel Bourgeois le 23 Septembre 2017
// Déclaration des fonctions associés a une carte

#include <vector>
#include <string>
#include <fstream>

enum Action
{
	Haut = 'w',
	Gauche = 'a',
	Bas = 's',
	Droite = 'd',
	Quitter = 'q'
};
enum Symbole
{
	PacMan = '0',
	Mur = '#',
	Pilule = 'o',
	Fantome = 'M',
	Vide = ' '
};

// Lire une carte de fichier texte
// Retourne sous forme de vector<string> où chaque string est une ligne de la carte
std::vector<std::string>LireCarte(std::ifstream& Carte);

// Prend en parametre un vector<string>
// Retourne true seulement si elle est bien rectangulaire
// (Seuelement si toutes les lignes ont la meme longueur)
bool CarteEstRectangulaire(const std::vector<std::string>& PacMap);

// Prend en parametre un vector<string> reprentant une carte rectangulaire préalablement validée
// Retourne true seuelement si la carte ne comprend que des caractères valides:
bool CaractereSontValides(const std::vector<std::string>& PacMap);

// Prend en parametre un vector<string> représentant une carte rectangulaire préalablement validée
// Retourne la hauteur de la carte
short CalculerHauteurCarte(const std::vector<std::string>& PacMap);

// Prend en paramètre un vector<string> représentant une carte rectangulaire préalablement validée
// Retourne la largeur de la carte
short CalculerLargeurCarte(const std::vector<std::string>& PacMap);

// Prend en paramètre un vector<string> représentant une carte rectangulaire préalablement validée
// Affiche la carte
void AfficherCarte(const std::vector<std::string>& PacMap);

// Vérifie si la carte respecte les critères de validation
// Retourne true si la carte est valide
bool CarteEstValide(const std::vector<std::string>& PacMap);

// Déplace PacMan dans la carte
void ActionPacMan(std::vector<std::string>& PacMap, char& Action);

// Change les actions majuscules pour des minuscules
void ActionMajuscules(char& TheAction);

#endif

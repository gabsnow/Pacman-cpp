#ifndef CHARACTER_H
#define CHARACTER_H
// Character.h
// Fait par Gabriel Bourgeois le 26 Novembre 2017
// Interface de la classe CCharacter

#include "sdlclg.h"
#include "Pacman.h"
#include "Object.h"
#include <map>

class CCharacter :
	public CObject
{
protected:
	// État de vie du personnage
	bool Vivant_;
	// Direction du personnage
	Direction Direction_;
	// Conteneur indiquant les directions possibles du personnage
	std::map<Direction, bool>Bouger_;
public:
	// Constructeur avec paramètres par défaut
	CCharacter(const int& X = 0, const int& Y = 0, const Direction& DirectionInit = D_None);
	// Accesseurs
	std::map<Direction, bool> GetBouger()const { return Bouger_; }
	Direction GetDirection()const { return Direction_; }
	bool GetVivant()const { return Vivant_; }
	// Mutateurs
	void SetBouger(Object Tableau[][Width], const int& HauteurTab);
	void SetDirection(const Direction& LaDirection);
	void SetVivant(const bool& Vivant);

	// Méthodes

	// Chasser
	// Intrant: Personnage Proie (celui que l'on souhaite chasser), Tableau d'objet 2D qui représente la carte
	// Pourchasse le personnage donné en argument en tentant de se rapprocher le plus possible, si plusieurs directions
	// pour se rapprocher sont possibles, génère une direction au hasard, si aucun rapprochement n'est possible,
	// la méthode "SePromener" est apelée pour un tour.
	void Chasser(const CCharacter& Proie, Object Carte[][Width], const int& HauteurCarte);
	// Déplacer
	// Intrant: La direction dans laquelle déplacer le personnage
	// Déplace le personnage de une case vers la direction donnée en paramètre
	void Deplacer(const Direction& LaDirection);
	// DéplacerBas
	// Déplace le personnage de une case vers le bas
	void DeplacerBas();
	// DéplacerDroite
	// Déplace le personnage de une case vers la droite
	void DeplacerDroite();
	// DéplacerGauche
	// Déplace le personnage de une case vers la gauche
	void DeplacerGauche();
	// DéplacerHaut
	// Déplace le personnage de une case vers le haut
	void DeplacerHaut();
	// DirectionCible
	// Intrants: Personnage ciblé
	// Extrant: Map de directions, bool
	// Détermine dans quelle(s) direction(s) se trouve le personnage cible par rapport au personnage actuel et 
	// initialise une map avec ces données
	std::map<Direction, bool> DirectionCible(const CCharacter& Cible);
	// Fuir
	// Intrants: Personnage Chasseur (celui que l'on souhaite fuir), Tableau d'objet 2D qui représente la carte
	// Fuis le personnage donné en argument en tentant de s'éloigner le plus possible, si plusieurs directions
	// pour s'éloigner sont possibles, génère une direction au hasard, si aucun éloignement n'est possible,
	// la méthode "SePromener" est apelée pour un tour.
	void Fuir(const CCharacter& Chasseur, Object Carte[][Width], const int& HauteurCarte);
	// GererActions
	// Intrants: Action, Tableau 2D qui représente la carte
	// Gere les actions de déplacements du personnage
	void GererDeplacements(const Event& Action, Object Carte[][Width], const int& HauteurCarte);
	// SePromener
	// Intrant: Tableau d'objet 2D qui représente la carte
	// Promène le personnage dans une direction au hasard, sans jamais le faire revenir sur ses pas, à moins que ça ne soit
	// la seule option possible
	void SePromener(Object Carte[][Width], const int& HauteurCarte);
	// Téléporter
	// Intrant: La direction dans laquelle téléporter le personnage
	// Téléporte le personnage vers la direction donnée en parametre
	void Teleporter(const Direction& LaDirection);
	// TéléporterBas
	// Téléporte le personnage vers le bas
	void TeleporterBas();
	// TéléporterDroite
	// Téléporte le personnage vers la droite
	void TeleporterDroite();
	// TéléporterGauche
	// Téléporte le personnage vers la gauche
	void TeleporterGauche();
	// TéléporterHaut
	// Téléporte le personnage vers le haut
	void TeleporterHaut();
	// TeleportationPossible
	// Intrants: Une Direction, un tableau 2D de type objet qui représente une carte, la hauteur de la carte
	// Extrants: Vrai ou Faux selon si le personnage présent peut se téléporter vers la direction donnée en argument
	// Vérifie si le personnage peut se téléporter vers la direction selon la carte 
	bool TeleportationPossible(const Direction& LaDirection, Object Carte[][Width], const int& HauteurCarte);

	// Surcharges d'opérateurs

	// Surcharge de l'opérateur "=="
	// Intrant: Personnage "Autre" avec lequel ce personnage sera comparé
	// Extrant: Retourne "true" si les personnages comparés ont la même position X et Y
	// Compare le personnage avec celui passé en argument, pour vérifier s'ils se trouvent à la même position,
	// si les deux personnages sont exactement a la meme position ^(X et Y), renvoi true, sinon, renvoi false.
	bool operator==(const CCharacter& Autre);
	// Surcharge de l'opérateur "!="
	// Intrant: Personnage "Autre" avec lequel ce personnage sera comparé
	// Extrant: Retourne "true" si les personnages comparés n'ont pas la même position X et Y
	// Renvoi l'oposé de la surcharge de l'opérateur "=="
	bool operator!=(const CCharacter& Autre);
};

#endif // !PERSONNAGE_H

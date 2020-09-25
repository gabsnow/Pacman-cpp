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
	// �tat de vie du personnage
	bool Vivant_;
	// Direction du personnage
	Direction Direction_;
	// Conteneur indiquant les directions possibles du personnage
	std::map<Direction, bool>Bouger_;
public:
	// Constructeur avec param�tres par d�faut
	CCharacter(const int& X = 0, const int& Y = 0, const Direction& DirectionInit = D_None);
	// Accesseurs
	std::map<Direction, bool> GetBouger()const { return Bouger_; }
	Direction GetDirection()const { return Direction_; }
	bool GetVivant()const { return Vivant_; }
	// Mutateurs
	void SetBouger(Object Tableau[][Width], const int& HauteurTab);
	void SetDirection(const Direction& LaDirection);
	void SetVivant(const bool& Vivant);

	// M�thodes

	// Chasser
	// Intrant: Personnage Proie (celui que l'on souhaite chasser), Tableau d'objet 2D qui repr�sente la carte
	// Pourchasse le personnage donn� en argument en tentant de se rapprocher le plus possible, si plusieurs directions
	// pour se rapprocher sont possibles, g�n�re une direction au hasard, si aucun rapprochement n'est possible,
	// la m�thode "SePromener" est apel�e pour un tour.
	void Chasser(const CCharacter& Proie, Object Carte[][Width], const int& HauteurCarte);
	// D�placer
	// Intrant: La direction dans laquelle d�placer le personnage
	// D�place le personnage de une case vers la direction donn�e en param�tre
	void Deplacer(const Direction& LaDirection);
	// D�placerBas
	// D�place le personnage de une case vers le bas
	void DeplacerBas();
	// D�placerDroite
	// D�place le personnage de une case vers la droite
	void DeplacerDroite();
	// D�placerGauche
	// D�place le personnage de une case vers la gauche
	void DeplacerGauche();
	// D�placerHaut
	// D�place le personnage de une case vers le haut
	void DeplacerHaut();
	// DirectionCible
	// Intrants: Personnage cibl�
	// Extrant: Map de directions, bool
	// D�termine dans quelle(s) direction(s) se trouve le personnage cible par rapport au personnage actuel et 
	// initialise une map avec ces donn�es
	std::map<Direction, bool> DirectionCible(const CCharacter& Cible);
	// Fuir
	// Intrants: Personnage Chasseur (celui que l'on souhaite fuir), Tableau d'objet 2D qui repr�sente la carte
	// Fuis le personnage donn� en argument en tentant de s'�loigner le plus possible, si plusieurs directions
	// pour s'�loigner sont possibles, g�n�re une direction au hasard, si aucun �loignement n'est possible,
	// la m�thode "SePromener" est apel�e pour un tour.
	void Fuir(const CCharacter& Chasseur, Object Carte[][Width], const int& HauteurCarte);
	// GererActions
	// Intrants: Action, Tableau 2D qui repr�sente la carte
	// Gere les actions de d�placements du personnage
	void GererDeplacements(const Event& Action, Object Carte[][Width], const int& HauteurCarte);
	// SePromener
	// Intrant: Tableau d'objet 2D qui repr�sente la carte
	// Prom�ne le personnage dans une direction au hasard, sans jamais le faire revenir sur ses pas, � moins que �a ne soit
	// la seule option possible
	void SePromener(Object Carte[][Width], const int& HauteurCarte);
	// T�l�porter
	// Intrant: La direction dans laquelle t�l�porter le personnage
	// T�l�porte le personnage vers la direction donn�e en parametre
	void Teleporter(const Direction& LaDirection);
	// T�l�porterBas
	// T�l�porte le personnage vers le bas
	void TeleporterBas();
	// T�l�porterDroite
	// T�l�porte le personnage vers la droite
	void TeleporterDroite();
	// T�l�porterGauche
	// T�l�porte le personnage vers la gauche
	void TeleporterGauche();
	// T�l�porterHaut
	// T�l�porte le personnage vers le haut
	void TeleporterHaut();
	// TeleportationPossible
	// Intrants: Une Direction, un tableau 2D de type objet qui repr�sente une carte, la hauteur de la carte
	// Extrants: Vrai ou Faux selon si le personnage pr�sent peut se t�l�porter vers la direction donn�e en argument
	// V�rifie si le personnage peut se t�l�porter vers la direction selon la carte 
	bool TeleportationPossible(const Direction& LaDirection, Object Carte[][Width], const int& HauteurCarte);

	// Surcharges d'op�rateurs

	// Surcharge de l'op�rateur "=="
	// Intrant: Personnage "Autre" avec lequel ce personnage sera compar�
	// Extrant: Retourne "true" si les personnages compar�s ont la m�me position X et Y
	// Compare le personnage avec celui pass� en argument, pour v�rifier s'ils se trouvent � la m�me position,
	// si les deux personnages sont exactement a la meme position ^(X et Y), renvoi true, sinon, renvoi false.
	bool operator==(const CCharacter& Autre);
	// Surcharge de l'op�rateur "!="
	// Intrant: Personnage "Autre" avec lequel ce personnage sera compar�
	// Extrant: Retourne "true" si les personnages compar�s n'ont pas la m�me position X et Y
	// Renvoi l'opos� de la surcharge de l'op�rateur "=="
	bool operator!=(const CCharacter& Autre);
};

#endif // !PERSONNAGE_H

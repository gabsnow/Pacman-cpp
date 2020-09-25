// Personnage.cpp
// Fait par Gabriel Bourgeois le 26 Novembre 2017
// Implémentation de la classe CPersonnage

#include "Pacman.h"
#include "Character.h"
#include <cstdlib>

// Constructeur
CCharacter::CCharacter(const int& X, const int& Y, const Direction& DirectionInit) : CObject(X, Y), Direction_(DirectionInit), Vivant_(true) {
}

int* Pointeur;


// Mutateurs
void CCharacter::SetBouger(Object Carte[][Width], const int& HauteurCarte) {
	Bouger_[D_Right] = Carte[this->GetYBox()][this->GetXBox() + 1] != H && Carte[this->GetYBox()][this->GetXBox() + 1] != W &&
		Carte[this->GetYBox()][this->GetXBox() + 1] != R && Carte[this->GetYBox()][this->GetXBox() + 1] != L &&
		Carte[this->GetYBox()][this->GetXBox() + 1] != H && Carte[this->GetYBox()][this->GetXBox() + 1] != D|| TeleportationPossible(D_Right, Carte, HauteurCarte);
	Bouger_[D_Left] = Carte[this->GetYBox()][this->GetXBox() - 1] != H && Carte[this->GetYBox()][this->GetXBox() - 1] != W &&
		Carte[this->GetYBox()][this->GetXBox() - 1] != R && Carte[this->GetYBox()][this->GetXBox() - 1] != L &&
		Carte[this->GetYBox()][this->GetXBox() - 1] != H && Carte[this->GetYBox()][this->GetXBox() - 1] != D || TeleportationPossible(D_Left, Carte, HauteurCarte);
	Bouger_[D_Up] = Carte[this->GetYBox() - 1][this->GetXBox()] != H && Carte[this->GetYBox() - 1][this->GetXBox()] != W &&
		Carte[this->GetYBox() - 1][this->GetXBox()] != R && Carte[this->GetYBox() - 1][this->GetXBox()] != L &&
		Carte[this->GetYBox() - 1][this->GetXBox()] != H && Carte[this->GetYBox() - 1][this->GetXBox()] != D || TeleportationPossible(D_Up, Carte, HauteurCarte);
	Bouger_[D_Down] = Carte[this->GetYBox() + 1][this->GetXBox()] != H && Carte[this->GetYBox() + 1][this->GetXBox()] != W &&
		Carte[this->GetYBox() + 1][this->GetXBox()] != R && Carte[this->GetYBox() + 1][this->GetXBox()] != L &&
		Carte[this->GetYBox() + 1][this->GetXBox()] != H && Carte[this->GetYBox() + 1][this->GetXBox()] != D || TeleportationPossible(D_Down, Carte, HauteurCarte);
	switch (this->GetDirection()) {
	case D_Right:
		Bouger_[D_None] = !Bouger_[D_Right] && !Bouger_[D_Up] && !Bouger_[D_Down];
		break;
	case D_Left:
		Bouger_[D_None] = !Bouger_[D_Left] && !Bouger_[D_Up] && !Bouger_[D_Down];
		break;
	case D_Up:
		Bouger_[D_None] = !Bouger_[D_Right] && !Bouger_[D_Left] && !Bouger_[D_Up];
		break;
	case D_Down:
		Bouger_[D_None] = !Bouger_[D_Right] && !Bouger_[D_Left] && !Bouger_[D_Down];
		break;
	}
}
void CCharacter::SetDirection(const Direction& LaDirection) {
	Direction_ = LaDirection;
}
void CCharacter::SetVivant(const bool& Vivant) {
	Vivant_ = Vivant;
}

// Méthodes

void CCharacter::Chasser(const CCharacter& Proie, Object Carte[][Width], const int& HauteurCarte) {
	SetBouger(Carte, HauteurCarte);

	std::map<Direction, bool> ProieVers = DirectionCible(Proie);

	bool Valid(false);
	Direction RandomDirection(D_None);

	if (!ProieVers[D_Right] && !ProieVers[D_Left]) {
		if (ProieVers[D_Down] && Bouger_[D_Down])
			DeplacerBas();
		else if (ProieVers[D_Up] && Bouger_[D_Up])
			DeplacerHaut();
		else
			SePromener(Carte, HauteurCarte);
	}
	else if (!ProieVers[D_Down] && !ProieVers[D_Up]) {
		if (ProieVers[D_Right] && Bouger_[D_Right])
			DeplacerDroite();
		else if (ProieVers[D_Left] && Bouger_[D_Left])
			DeplacerGauche();
		else
			SePromener(Carte, HauteurCarte);
	}
	else {
		for (int i(1); i < 5 && !Valid; ++i)
			Valid = ProieVers[itod(i)] && Bouger_[itod(i)];
		if (Valid) {
			do {
				RandomDirection = itod(rand() % 4 + 1);
				Valid = ProieVers[RandomDirection] && Bouger_[RandomDirection];
			} while (!Valid);
			Deplacer(RandomDirection);
		}
		else {
			SePromener(Carte, HauteurCarte);
		}
	}
}
void CCharacter::Deplacer(const Direction& LaDirection) {
	switch (LaDirection)
	{
	case D_Right:
		DeplacerDroite();
		break;
	case D_Left:
		DeplacerGauche();
		break;
	case D_Up:
		DeplacerHaut();
		break;
	case D_Down:
		DeplacerBas();
		break;
	}
}
void CCharacter::DeplacerBas() {
	SetYBox(GetY() / PixelsPerBox + 1);
	SetDirection(D_Down);
}
void CCharacter::DeplacerDroite() {
	SetXBox(GetX() / PixelsPerBox + 1);
	SetDirection(D_Right);
}
void CCharacter::DeplacerGauche() {
	SetXBox(GetX() / PixelsPerBox - 1);
	SetDirection(D_Left);
}
void CCharacter::DeplacerHaut() {
	SetYBox(GetY() / PixelsPerBox - 1);
	SetDirection(D_Up);
}
std::map<Direction, bool> CCharacter::DirectionCible(const CCharacter& Cible) {
	std::map<Direction, bool> CibleVers;
	int DistanceX(Cible.GetXBox() - GetXBox());
	int DistanceY(Cible.GetYBox() - GetYBox());

	CibleVers[D_Right] = DistanceX > 0;
	CibleVers[D_Left] = DistanceX < 0;
	CibleVers[D_Down] = DistanceY > 0;
	CibleVers[D_Up] = DistanceY < 0;

	return CibleVers;
}
void CCharacter::Fuir(const CCharacter& Chasseur, Object Carte[][Width], const int& HauteurCarte) {
	SetBouger(Carte, HauteurCarte);

	std::map<Direction, bool> ChasseurVers = DirectionCible(Chasseur);

	bool Valid(false);
	Direction RandomDirection(D_None);

	if (!ChasseurVers[D_Right] && !ChasseurVers[D_Left]) {
		if (ChasseurVers[D_Down] && Bouger_[D_Up]) {
			if (TeleportationPossible(D_Up, Carte, HauteurCarte))
				TeleporterHaut();
			else
				DeplacerHaut();
		}
		else if (ChasseurVers[D_Up] && Bouger_[D_Down]) {
			if (TeleportationPossible(D_Down, Carte, HauteurCarte))
				TeleporterBas();
			else
				DeplacerBas();
		}
		else
			SePromener(Carte, HauteurCarte);
	}
	else if (!ChasseurVers[D_Down] && !ChasseurVers[D_Up]) {
		if (ChasseurVers[D_Right] && Bouger_[D_Left]) {
			if (TeleportationPossible(D_Left, Carte, HauteurCarte))
				TeleporterGauche();
			else
				DeplacerGauche();
		}
		else if (ChasseurVers[D_Left] && Bouger_[D_Right]) {
			if (TeleportationPossible(D_Right, Carte, HauteurCarte))
				TeleporterDroite();
			else
				DeplacerDroite();
		}
		else
			SePromener(Carte, HauteurCarte);
	}
	else {
		for (int i(1); i < 5 && !Valid; ++i)
			Valid = ChasseurVers[itod(i)] && Bouger_[OppositeDirection(itod(i))];
		if (Valid) {
			do {
				RandomDirection = itod(rand() % 4 + 1);
				Valid = ChasseurVers[RandomDirection] && Bouger_[OppositeDirection(RandomDirection)];
			} while (!Valid);
			if (TeleportationPossible(OppositeDirection(RandomDirection), Carte, HauteurCarte))
				Teleporter(OppositeDirection(RandomDirection));
			else
				Deplacer(OppositeDirection(RandomDirection));
		}
		else
			SePromener(Carte, HauteurCarte);
	}
}
void CCharacter::GererDeplacements(const Event& Action, Object Carte[][Width], const int& HauteurCarte) {
	Direction LaDirection = etod(Action);
	if (LaDirection != D_None) {
		SetBouger(Carte, HauteurCarte);

		if (Bouger_[LaDirection] && TeleportationPossible(LaDirection, Carte, HauteurCarte))
			Teleporter(LaDirection);
		else if (Bouger_[LaDirection])
			Deplacer(LaDirection);
	}
}
void CCharacter::SePromener(Object Carte[][Width], const int& HauteurCarte) {
	Direction RandomDir(D_None);
	bool Valid(false);
	SetBouger(Carte, HauteurCarte);
	if (Bouger_[D_None]) {
		this->Deplacer(OppositeDirection(this->GetDirection()));
	}
	else {
		do {
			RandomDir = itod(rand() % 4 + 1);
			Valid = Bouger_[RandomDir] && OppositeDirection(this->GetDirection()) != RandomDir;
		} while (!Valid);
		this->GererDeplacements(dtoe(RandomDir), Carte, HauteurCarte);
	}
}
void CCharacter::Teleporter(const Direction& LaDirection) {
	switch (LaDirection) {
	case D_Right:
		TeleporterDroite();
		break;
	case D_Left:
		TeleporterGauche();
		break;
	case D_Up:
		TeleporterHaut();
		break;
	case D_Down:
		TeleporterBas();
		break;
	}
}
void CCharacter::TeleporterBas() {
	SetYBox(0);
	SetDirection(D_Down);
}
void CCharacter::TeleporterDroite() {
	SetXBox(0);
	SetDirection(D_Right);
}
void CCharacter::TeleporterGauche() {
	SetXBox(Width - 1);
	SetDirection(D_Left);
}
void CCharacter::TeleporterHaut() {
	SetYBox(Height - 1);
	SetDirection(D_Up);
}
bool CCharacter::TeleportationPossible(const Direction& LaDirection, Object Carte[][Width], const int& HauteurCarte) {
	bool Possible(false);

	switch (LaDirection) {
	case D_Right:
		Possible = this->GetXBox() == Width - 1 && Carte[this->GetYBox()][0] != W &&
			this->GetXBox() == Width - 1 && Carte[this->GetYBox()][0] != H &&
			this->GetXBox() == Width - 1 && Carte[this->GetYBox()][0] != R;
		break;
	case D_Left:
		Possible = this->GetXBox() == 0 && Carte[this->GetYBox()][Width - 1] != W &&
			this->GetXBox() == 0 && Carte[this->GetYBox()][Width - 1] != H &&
			this->GetXBox() == 0 && Carte[this->GetYBox()][Width - 1] != R;
		break;
	case D_Up:
		Possible = this->GetYBox() == 0 && Carte[Height - 1][this->GetXBox()] != W &&
			this->GetYBox() == 0 && Carte[Height - 1][this->GetXBox()] != H &&
			this->GetYBox() == 0 && Carte[Height - 1][this->GetXBox()] != R;
		break;
	case D_Down:
		Possible = this->GetYBox() == Height - 1 && Carte[0][this->GetXBox()] != W &&
			this->GetYBox() == Height - 1 && Carte[0][this->GetXBox()] != H &&
			this->GetYBox() == Height - 1 && Carte[0][this->GetXBox()] != R;
		break;
	default:
		Possible = false;
	}
	return Possible;
}

// Surcharges d'opérateurs

bool CCharacter::operator==(const CCharacter& Autre) {
	return GetX() == Autre.GetX() && GetY() == Autre.GetY();
}
bool CCharacter::operator!=(const CCharacter& Autre) {
	return !(*this == Autre);
}

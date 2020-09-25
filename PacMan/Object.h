#ifndef OBJECT_H
#define OBJECT_H
// Objet.h
// Fait par Gabriel Bourgeois le 28 Novembre 2017
// Interface de la classe CObject

#include "Pacman.h"

class CObject
{
protected:
	int X_;
	int Y_;
public:
	// Constructeur avec paramètres par défaut
	CObject(int PosX = 0, int PosY = 0);

	// Mutateurs
	void SetX(int X);
	void SetXBox(int X);
	void SetY(int Y);
	void SetYBox(int Y);

	// Accesseurs
	int GetX()const { return X_; }
	int GetXBox()const { return X_ / PixelsPerBox; }
	int GetY()const { return Y_; }
	int GetYBox()const { return Y_ / PixelsPerBox; }
};

#endif

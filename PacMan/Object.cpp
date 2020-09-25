// Objet.cpp
// Fait par Gabriel Bourgeois le 28 Novembre 2017
// Implémentation de la classe CObjet

#include "Object.h"
#include "Pacman.h"

CObject::CObject(int PosX, int PosY) : X_(PosX * PixelsPerBox), Y_(PosY * PixelsPerBox)
{

}
void CObject::SetX(int X)
{
	if (X <= Width * PixelsPerBox && X >= 0)
		X_ = X;
}
void CObject::SetY(int Y)
{
	if (Y <= Height * PixelsPerBox && Y >= 0)
		Y_ = Y;
}
void CObject::SetXBox(int X)
{
	if (X * PixelsPerBox <= Width * PixelsPerBox && X * PixelsPerBox >= 0)
		X_ = X * PixelsPerBox;
}
void CObject::SetYBox(int Y)
{
	if (Y * PixelsPerBox <= Height * PixelsPerBox && Y * PixelsPerBox >= 0)
		Y_ = Y*PixelsPerBox;
}
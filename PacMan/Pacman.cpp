// PacMan.cpp
// Fait par Gabriel Bourgeois le 28 Novembre 2017
// Implémentation de la classe CPacManGame

#include "sdlclg.h"
#include "Pacman.h"

std::string mtos(Menu TheMenu)
{
	std::string StringMenu("");
	switch (TheMenu)
	{
	case M_Credits:
		StringMenu = "Credits";
		break;
	case M_Options:
		StringMenu = "Options";
		break;
	case M_Main:
		StringMenu = "Menu";
		break;
	case M_Themes:
		StringMenu = "Themes";
		break;
	case M_Custom:
		StringMenu = "Custom";
		break;
	case M_CustomPacman:
		StringMenu = "CustomPacman";
		break;
	case M_CustomGhosts:
		StringMenu = "CustomGhosts";
		break;
	case M_CustomFood:
		StringMenu = "CustomFood";
		break;
	case M_CustomPower:
		StringMenu = "CustomPower";
		break;
	case M_CustomWall:
		StringMenu = "CustomWalls";
		break;
	case M_CustomHazard:
		StringMenu = "CustomHazard";
		break;
	case M_CustomCannon:
		StringMenu = "CustomCannon";
		break;
	case M_CustomBullet:
		StringMenu = "CustomBullet";
		break;
	case M_Pause:
		StringMenu = "Pause";
		break;
	case M_Won:
		StringMenu = "Won";
		break;
	case M_Gameover:
		StringMenu = "GameOver";
		break;
	default:
		StringMenu = "Aucun";
	}
	return StringMenu;
}
Event dtoe(Direction TheDirection)
{
	Event TheEvent(EVAucun);

	switch (TheDirection)
	{
	case D_Right:
		TheEvent = EVRight;
		break;
	case D_Left:
		TheEvent = EVLeft;
		break;
	case D_Up:
		TheEvent = EVUp;
		break;
	case D_Down:
		TheEvent = EVDown;
		break;
	default:
		TheEvent = EVAucun;
	}

	return TheEvent;
}
Direction etod(Event TheEvent)
{
	Direction UneDirection(D_None);

	switch (TheEvent)
	{
	case EVRight:
		UneDirection = D_Right;
		break;
	case EVLeft:
		UneDirection = D_Left;
		break;
	case EVUp:
		UneDirection = D_Up;
		break;
	case EVDown:
		UneDirection = D_Down;
		break;
	default:
		UneDirection = D_None;
	}

	return UneDirection;
}
Direction itod(int Int)
{
	Direction UneDirection;
	switch (Int)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		UneDirection = static_cast<Direction>(Int);
		break;
	default:
		UneDirection = D_None;
	}
	return UneDirection;
}
std::string ttos(Theme TheTheme)
{
	std::string StringTheme("");
	switch (TheTheme) {
	case T_Pacman1:
		StringTheme = "Pacman1";
		break;
	case T_Pacman2:
		StringTheme = "Pacman2";
		break;
	case T_Evil:
		StringTheme = "Evil";
		break;
	case T_Pacmario:
		StringTheme = "Pacmario";
		break;
	case T_Mario:
		StringTheme = "Mario";
		break;
	case T_Kirby:
		StringTheme = "Kirby";
		break;
	case T_Glitched:
		StringTheme = "Glitched";
		break;
	case T_Custom:
		StringTheme = "Custom";
		break;
	default:
		StringTheme = "None";
	}
	return StringTheme;
}
Direction OppositeDirection(Direction TheDirection)
{
	Direction DirectionOpose;

	switch (TheDirection)
	{
	case D_Right:
		DirectionOpose = D_Left;
		break;
	case D_Left:
		DirectionOpose = D_Right;
		break;
	case D_Down:
		DirectionOpose = D_Up;
		break;
	case D_Up:
		DirectionOpose = D_Down;
		break;
	default:
		DirectionOpose = D_None;
	}

	return DirectionOpose;
}

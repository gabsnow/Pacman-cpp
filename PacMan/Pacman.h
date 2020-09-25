#ifndef _PACMAN_H
#define _PACMAN_H

#include "sdlclg.h"
using namespace std;

// Déclarations de constantes requises pour le jeu
const int PixelsPerBox = 24;

const int Height = 21, Width = 19;
const int PixHeight = Height * PixelsPerBox, PixWidth = Width * PixelsPerBox;
const int LevelTest = NULL, LevelLast = 4;
const int CannonSpeed = 50, GhostSpeed = 10; // Les cannons tirent à tous les 50 tours et les fantomes bougent aux 10 tours
const int PowerTime = 150; // Le pouvoir d'invincibilité dure 150 tours

// Énumération pour représenter les objets dans la carte pacman
// V = Void, W= Wall, F = Food, P = Power,
// R = Right Cannon, L = Left Cannon, H = Cannon Haut, B = Cannon Bas, H = Hazard
enum Object { V = 100, W, F, P, R, L, U, D, H};

// Selections du menu
enum Selection {
	S_None, 
	S_Principal_Jouer, S_Principal_Options, S_Principal_Quitter,
	S_Options_Themes, S_Options_Credits, S_Options_Return,
	S_Themes_Pacman1, S_Themes_Pacman2, S_Themes_Evil, S_Themes_Pacmario, S_Themes_Mario, S_Themes_Kirby, S_Themes_Glitched, S_Themes_Custom, S_Themes_Return,
	S_Credits_Return,
	S_Pause_Resume, S_Pause_Options, S_Pause_Quit,
	S_Won_Replay, S_Won_Menu, S_Won_Quit,
	S_GameOver_Retry, S_GameOver_Menu, S_GameOver_Quit,
	S_Custom_Pacman, S_Custom_Ghosts, S_Custom_Food, S_Custom_Power, S_Custom_Walls, S_Custom_Hazard, S_Custom_Cannon, S_Custom_Bullet, S_Custom_Return,
	S_CustomPacman_Pacman1, S_CustomPacman_Pacman2, S_CustomPacman_Evil, S_CustomPacman_Pacmario, S_CustomPacman_Mario, S_CustomPacman_Kirby, S_CustomPacman_Return,
	S_CustomGhosts_Pacman1, S_CustomGhosts_Pacman2, S_CustomGhosts_Evil, S_CustomGhosts_Pacmario, S_CustomGhosts_Mario, S_CustomGhosts_Kirby, S_CustomGhosts_Return,
	S_CustomFood_Pacman1, S_CustomFood_Pacman2, S_CustomFood_Evil, S_CustomFood_Pacmario, S_CustomFood_Mario, S_CustomFood_Kirby, S_CustomFood_Return,
	S_CustomPower_Pacman1, S_CustomPower_Pacman2, S_CustomPower_Evil, S_CustomPower_Pacmario, S_CustomPower_Mario, S_CustomPower_Kirby, S_CustomPower_Return,
	S_CustomWall_Pacman1, S_CustomWall_Pacman2, S_CustomWall_Evil, S_CustomWall_Pacmario, S_CustomWall_Mario, S_CustomWall_Kirby, S_CustomWall_Return,
	S_CustomHazard_Pacman1, S_CustomHazard_Pacman2, S_CustomHazard_Evil, S_CustomHazard_Pacmario, S_CustomHazard_Mario, S_CustomHazard_Kirby, S_CustomHazard_Return,
	S_CustomCannon_Pacman1, S_CustomCannon_Pacman2, S_CustomCannon_Evil, S_CustomCannon_Pacmario, S_CustomCannon_Mario, S_CustomCannon_Kirby, S_CustomCannon_Return,
	S_CustomBullet_Pacman1, S_CustomBullet_Pacman2, S_CustomBullet_Evil, S_CustomBullet_Pacmario, S_CustomBullet_Mario, S_CustomBullet_Kirby, S_CustomBullet_Return
};

// Menus du jeu
enum Menu {
	M_None, 
	M_Pause, M_Gameover, M_Won,
	M_Main,
	M_Options, 
	M_Themes, M_Credits,
	M_Custom,
	M_CustomPacman, M_CustomGhosts, M_CustomFood, M_CustomPower, M_CustomWall, M_CustomHazard, M_CustomCannon, M_CustomBullet
};

// Thèmes du jeu
enum Theme {
	T_None, T_Pacman1, T_Pacman2, T_Evil, T_Pacmario, T_Mario, T_Kirby, T_Glitched, T_Custom
};

// Directions d'un personnage. D_Aucune = Pas de direction (ou aucune direction disponible)
enum Direction {
	D_None,
	D_Right,
	D_Left,
	D_Up,
	D_Down
};

// OppositeDirection
// Intrant: Une direction
// Extrant: Direction oposée à celle donnée en argument
// Fonction qui renvoi la direction oposée de celle donnée en argument
Direction OppositeDirection(Direction TheDirection);

// dtoe (Direction to Evenement)
// Intrant: Valeur de type "Direction"
// Extrant: Valeur de type "Evenement"
// Fonction qui transforme un "Direction" en un "Evenement", si aucun Evenement ne correspond, renvoi l'évenement "EVAucun"
Event dtoe(Direction LaDirection);

// etod (Evennement to Direction)
// Intrant: Valeur de type "Evenement"
// Extrant: Valeur de type "Direction"
// Fonction qui transforme un "Evenement" en un "Direction", si aucun evenement ne correspond, renvoi la Direction "Aucune"
Direction etod(Event TheEvent);

// itod (int to Direction)
// Intrant: Valeur de type entière
// Extrant: Valeur de type "Direction"
// Transforme un int en un "Direction", si aucun int ne correspond, renvoi la Direction "Aucune"
Direction itod(int Int);

// mtos (Menu to String)
// Intrant: Valeur de type "Menu"
// Extrant: Valeur de type "String"
// Transforme un Menu en String
std::string mtos(Menu TheMenu);

// ttos (Theme to String)
// Intrant: Valeur de type "Theme"
// Extrant: Valeur de type "String"
// Renvoi le mot ou le groupe de mots (en string) qui décrit le thème passé en argument
std::string ttos(Theme TheTheme);

#endif
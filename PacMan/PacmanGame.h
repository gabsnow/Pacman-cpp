#ifndef PACMANGAME_H
#define PACMANGAME_H
// PacManGame.h
// Fait par Gabriel Bourgeois le 28 Novembre 2017
// Interface de la classe CPacman

#include "sdlclg.h"
#include "Pacman.h"
#include "Character.h"
#include <map>
#include <vector>

class CPacman {
private:
	int Frame_;
	int FrameCannonShot_;
	int FrameInvincible_;
	int Level_;
	bool Playing_;
	bool Invincible_;
	bool FoodLeft_;
	bool GameOver_;
	bool Pause_;
	Event Action_;
	CObject Cursor_;
	Selection CursorSelection_;
	Menu Menu_;
	Theme Theme_;
	Object Map_[Height][Width];
	std::vector<CCharacter> Bullets_;
	std::map<std::string, CCharacter> Characters_;
	std::map<std::string, CObject> CheckMarks_;
	std::map<std::string, std::string>TexturePaths_;
	std::map<std::string, ImageId>Textures_;
public:
	// Constructeur paramétrique
	CPacman();
	// Destructeur
	~CPacman();

	// Mutateurs
	void SetAction(Event Action);
	void SetCheckMarksY(int Y);
	void SetCursor(const Selection& TheSelection);
	void SetFoodLeft(const bool& FoodLeft);
	void SetFrame(const int& Frame);
	void SetFrameCannonShot(const int& FrameCannonShot);
	void SetFrameInvincible(const int& FrameInvincible);
	void SetGameOver();
	void SetGameOver(const bool& GameOver);
	void SetInvincible(const bool& Invincible);
	void SetLevel(const short& Level);
	void SetMap(const Object Map[][Width], const int& MapHeight);
	void SetMenu(const Menu& TheMenu);
	void SetPause(const bool& Pause);
	void SetPlaying(const bool& Playing);
	void SetTexturePath(const std::string& TextureType, const std::string& Path);
	void SetTexturePaths();
	void SetTextures();
	void SetTheme(const Theme& TheTheme);

	// Accesseurs
	Event GetAction()const { return Action_; }
	std::vector<CCharacter> GetBullets()const { return Bullets_; }
	std::map<std::string, CCharacter> GetCharacters()const { return Characters_; }
	std::map<std::string, CObject> GetCheckMarks()const { return CheckMarks_; }
	Selection GetCursorSelection()const { return CursorSelection_; }
	bool GetFoodLeft()const { return FoodLeft_; }
	int GetFrame()const { return Frame_; }
	int GetFrameCannonShot()const { return FrameCannonShot_; }
	int GetFrameInvincible()const { return FrameInvincible_; }
	bool GetGameOver()const { return GameOver_; }
	bool GetInvincible()const { return Invincible_; }
	int GetLevel()const { return Level_; }
	Menu GetMenu()const { return Menu_; }
	bool GetPause()const { return Pause_; }
	bool GetPlaying()const { return Playing_; }
	std::map<std::string, std::string> GetTexturePaths()const { return TexturePaths_; }
	std::map<std::string, ImageId> GetTextures()const { return Textures_; }
	Theme GetTheme()const { return Theme_; }

	// Méthodes

	// GhostWarp
	// Intrant: Un Fantome (de type CCharacter)
	// Replace le fantome donné en argument au centre de la carte (9, 9)
	void GhostWarp(CCharacter& Ghost);
	// InitializeGame
	// Initialise ou re-initialise les attributs du jeu pour les débuts de niveaux
	void InitializeGame();
	// ManageSelection
	// Gere les instructions lorsque l'on est dans le menu
	void ManageSelection();
	// MoveCursor
	// Gere la position du curseur
	void MoveCursor();
	// Play
	// Permet de jouer a Pacman
	void Play();
	// ShowGame
	// Affiche la carte et les objets qui ne sont pas dans la carte (pacman, les fantomes, les balles)
	void ShowGame();
	// ShowLevelEnd
	// Affiche les options de fin de niveau (l'echelle et la porte)
	void ShowLevelEnd();
	// ShowMenu
	// Affiche le bon menu selon où le joueur se trouve
	void ShowMenu();
};

#endif

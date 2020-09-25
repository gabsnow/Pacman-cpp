// PacMan.cpp
// Fait par Gabriel Bourgeois le 28 Novembre 2017
// Implémentation de la classe CPacman

#include "sdlclg.h"
#include "Pacman.h"
#include "Character.h"
#include "Pacmangame.h"

CPacman::CPacman() :Playing_(false), Level_(4) {
	InitializeDisplay("Pacman", PixWidth, PixHeight);

	CheckMarks_["Theme"].SetX(290);
	CheckMarks_["Pacman"].SetX(290);
	CheckMarks_["Ghosts"].SetX(290);
	CheckMarks_["Food"].SetX(290);
	CheckMarks_["Power"].SetX(290);
	CheckMarks_["Wall"].SetX(290);
	CheckMarks_["Hazard"].SetX(290);
	CheckMarks_["Cannon"].SetX(290);
	CheckMarks_["Bullet"].SetX(290);

	InitializeGame();

	SetMenu(M_Main);
	SetTheme(T_Pacman1);
}
CPacman::~CPacman() {
	QuitDisplay();
}

// Mutateurs
void CPacman::SetAction(Event Action) {
	if (!GetGameOver() && !GetInvincible() && GetMenu() == M_None) {
		switch (Action) {
		case EVRight:
			Characters_["Pacman"].SetVivant(!(Map_[Characters_["Pacman"].GetYBox()][Characters_["Pacman"].GetXBox() + 1] == H));
			break;
		case EVLeft:
			Characters_["Pacman"].SetVivant(!(Map_[Characters_["Pacman"].GetYBox()][Characters_["Pacman"].GetXBox() - 1] == H));
			break;
		case EVUp:
			Characters_["Pacman"].SetVivant(!(Map_[Characters_["Pacman"].GetYBox() - 1][Characters_["Pacman"].GetXBox()] == H));
			break;
		case EVDown:
			Characters_["Pacman"].SetVivant(!(Map_[Characters_["Pacman"].GetYBox() + 1][Characters_["Pacman"].GetXBox()] == H));
			break;
		}

		SetGameOver(!Characters_["Pacman"].GetVivant());

		if (GetGameOver())
			Action = EVAucun;
	}

	if (Action == EVQuit && GetMenu() == M_None)
		Action = EVKEY_P;

	if (!GetGameOver() && GetPlaying() && Action == EVKEY_P)
		SetPause(!GetPause());

	Action_ = Action;
}
void CPacman::SetCheckMarksY(int Y) {
	CheckMarks_["Theme"].SetY(Y);

	if (GetTheme() == T_Glitched)
		Y = PixHeight;

	CheckMarks_["Pacman"].SetY(Y);
	CheckMarks_["Ghosts"].SetY(Y);
	CheckMarks_["Food"].SetY(Y);
	CheckMarks_["Power"].SetY(Y);
	CheckMarks_["Wall"].SetY(Y);
	CheckMarks_["Hazard"].SetY(Y);
	CheckMarks_["Cannon"].SetY(Y);
	CheckMarks_["Bullet"].SetY(Y);
}
void CPacman::SetCursor(const Selection& TheSelection) {
	switch (TheSelection) {
	case S_Principal_Jouer:
		Cursor_.SetX(135);
		Cursor_.SetY(196);
		break;
	case S_Principal_Options:
		Cursor_.SetX(103);
		Cursor_.SetY(278);
		break;
	case S_Principal_Quitter:
		Cursor_.SetX(142);
		Cursor_.SetY(378);
		break;
	case S_Options_Themes:
		Cursor_.SetX(107);
		Cursor_.SetY(196);
		break;
	case S_Options_Credits:
		Cursor_.SetX(105);
		Cursor_.SetY(280);
		break;
	case S_Themes_Pacman1:
	case S_CustomPacman_Pacman1:
	case S_CustomGhosts_Pacman1:
	case S_CustomFood_Pacman1:
	case S_CustomPower_Pacman1:
	case S_CustomWall_Pacman1:
	case S_CustomHazard_Pacman1:
	case S_CustomCannon_Pacman1:
	case S_CustomBullet_Pacman1:
		Cursor_.SetX(115);
		Cursor_.SetY(172);
		break;
	case S_Themes_Pacman2:
	case S_CustomPacman_Pacman2:
	case S_CustomGhosts_Pacman2:
	case S_CustomFood_Pacman2:
	case S_CustomPower_Pacman2:
	case S_CustomWall_Pacman2:
	case S_CustomHazard_Pacman2:
	case S_CustomCannon_Pacman2:
	case S_CustomBullet_Pacman2:
		Cursor_.SetX(115);
		Cursor_.SetY(204);
		break;
	case S_Themes_Evil:
	case S_CustomPacman_Evil:
	case S_CustomGhosts_Evil:
	case S_CustomFood_Evil:
	case S_CustomPower_Evil:
	case S_CustomWall_Evil:
	case S_CustomHazard_Evil:
	case S_CustomCannon_Evil:
	case S_CustomBullet_Evil:
		Cursor_.SetX(100);
		Cursor_.SetY(238);
		break;
	case S_Themes_Pacmario:
	case S_CustomPacman_Pacmario:
	case S_CustomGhosts_Pacmario:
	case S_CustomFood_Pacmario:
	case S_CustomPower_Pacmario:
	case S_CustomWall_Pacmario:
	case S_CustomHazard_Pacmario:
	case S_CustomCannon_Pacmario:
	case S_CustomBullet_Pacmario:
		Cursor_.SetX(114);
		Cursor_.SetY(266);
		break;
	case S_Themes_Mario:
	case S_CustomPacman_Mario:
	case S_CustomGhosts_Mario:
	case S_CustomFood_Mario:
	case S_CustomPower_Mario:
	case S_CustomWall_Mario:
	case S_CustomHazard_Mario:
	case S_CustomCannon_Mario:
	case S_CustomBullet_Mario:
		Cursor_.SetX(133);
		Cursor_.SetY(295);
		break;
	case S_Themes_Kirby:
	case S_CustomPacman_Kirby:
	case S_CustomGhosts_Kirby:
	case S_CustomFood_Kirby:
	case S_CustomPower_Kirby:
	case S_CustomWall_Kirby:
	case S_CustomHazard_Kirby:
	case S_CustomCannon_Kirby:
	case S_CustomBullet_Kirby:
		Cursor_.SetX(137);
		Cursor_.SetY(322);
		break;
	case S_Themes_Glitched:
		Cursor_.SetX(124);
		Cursor_.SetY(353);
		break;
	case S_Themes_Custom:
		Cursor_.SetX(129);
		Cursor_.SetY(378);
		break;
	case S_Themes_Return:
	case S_Custom_Return:
	case S_CustomPacman_Return:
	case S_CustomGhosts_Return:
	case S_CustomFood_Return:
	case S_CustomPower_Return:
	case S_CustomWall_Return:
	case S_CustomHazard_Return:
	case S_CustomCannon_Return:
	case S_CustomBullet_Return:
		Cursor_.SetX(154);
		Cursor_.SetY(457);
		break;
	case S_Options_Return:
	case S_Credits_Return:
		Cursor_.SetX(110);
		Cursor_.SetY(440);
		break;
	case S_Pause_Resume:
		Cursor_.SetX(160);
		Cursor_.SetY(215);
		break;
	case S_Pause_Options:
		Cursor_.SetX(160);
		Cursor_.SetY(251);
		break;
	case S_Pause_Quit:
	case S_Won_Quit:
	case S_GameOver_Quit:
		Cursor_.SetX(178);
		Cursor_.SetY(285);
		break;
	case S_Won_Replay:
		Cursor_.SetX(168);
		Cursor_.SetY(215);
		break;
	case S_GameOver_Retry:
		Cursor_.SetX(173);
		Cursor_.SetY(215);
		break;
	case S_Won_Menu:
	case S_GameOver_Menu:
		Cursor_.SetX(173);
		Cursor_.SetY(251);
		break;
	case S_Custom_Pacman:
		Cursor_.SetX(152);
		Cursor_.SetY(171);
		break;
	case S_Custom_Ghosts:
		Cursor_.SetX(158);
		Cursor_.SetY(205);
		break;
	case S_Custom_Food:
		Cursor_.SetX(165);
		Cursor_.SetY(236);
		break;
	case S_Custom_Power:
		Cursor_.SetX(158);
		Cursor_.SetY(265);
		break;
	case S_Custom_Walls:
		Cursor_.SetX(162);
		Cursor_.SetY(295);
		break;
	case S_Custom_Hazard:
		Cursor_.SetX(149);
		Cursor_.SetY(323);
		break;
	case S_Custom_Cannon:
		Cursor_.SetX(149);
		Cursor_.SetY(350);
		break;
	case S_Custom_Bullet:
		Cursor_.SetX(158);
		Cursor_.SetY(379);
		break;
	}
	CursorSelection_ = TheSelection;
}
void CPacman::SetFoodLeft(const bool& FoodLeft) {
	FoodLeft_ = FoodLeft;
}
void CPacman::SetFrame(const int& Frame) {
	if (Frame > NULL && Frame < GhostSpeed)
		Frame_ = Frame;
	else
		Frame_ = NULL;

	SetFrameCannonShot(GetFrameCannonShot() + 1);

	if (GetInvincible())
		SetFrameInvincible(GetFrameInvincible() + 1);
}
void CPacman::SetFrameCannonShot(const int& FrameCannonShot)
{
	if (FrameCannonShot > NULL && FrameCannonShot <= CannonSpeed)
		FrameCannonShot_ = FrameCannonShot;
	else
		FrameCannonShot_ = NULL;

}
void CPacman::SetFrameInvincible(const int& FameInvincible) {
	if (FameInvincible > NULL && FameInvincible <= PowerTime)
		FrameInvincible_ = FameInvincible;
	else
		FrameInvincible_ = NULL;
}
void CPacman::SetGameOver() {
	if (!GetGameOver() && !GetInvincible()) {
		for (unsigned int i(NULL); !Bullets_.empty() && i < Bullets_.size() && Characters_["Pacman"].GetVivant(); ++i)
			Characters_["Pacman"].SetVivant(Characters_["Pacman"] != Bullets_[i]);
		if (Characters_["Pacman"].GetVivant())
			Characters_["Pacman"].SetVivant(Characters_["Pacman"] != Characters_["Shadow"] && Characters_["Pacman"] != Characters_["Bashful"] && Characters_["Pacman"] != Characters_["Speedy"] && Characters_["Pacman"] != Characters_["Pokey"]);
	}

	SetGameOver(!Characters_["Pacman"].GetVivant());
}
void CPacman::SetGameOver(const bool& GameOver) {
	if (GameOver)
		SetMenu(M_Gameover);
	GameOver_ = GameOver;
}
void CPacman::SetInvincible(const bool& Invincible) {
	Invincible_ = Invincible;
}
void CPacman::SetLevel(const short& Level) {
	if (Level == LevelTest || Level > NULL && Level <= LevelLast)
		Level_ = Level;
	else
		Level_ = NULL;

	if (GetLevel() == 1) {
		Object Tableau[Height][Width]{
			{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W },
			{ W, P, F, F, F, F, F, F, F, W, F, F, F, F, F, F, F, P, W },
			{ W, F, W, W, F, W, W, W, F, W, F, W, W, W, F, W, W, F, W },
			{ W, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, W },
			{ W, F, W, W, F, W, F, W, W, W, W, W, F, W, F, W, W, F, W },
			{ W, F, F, F, F, W, F, F, F, W, F, F, F, W, F, F, F, F, W },
			{ W, W, W, W, F, W, W, W, V, W, V, W, W, W, F, W, W, W, W },
			{ V, V, V, W, F, W, V, V, V, V, V, V, V, W, F, W, V, V, V },
			{ W, W, W, W, F, W, V, W, W, V, W, W, V, W, F, W, W, W, W },
			{ V, V, V, V, F, V, V, W, V, V, V, W, V, V, F, V, V, V, V },
			{ W, W, W, W, F, W, V, W, W, V, W, W, V, W, F, W, W, W, W },
			{ V, V, V, W, F, W, V, V, V, V, V, V, V, W, F, W, V, V, V },
			{ W, W, W, W, F, W, V, W, W, W, W, W, V, W, F, W, W, W, W },
			{ W, F, F, F, F, F, F, F, F, W, F, F, F, F, F, F, F, F, W },
			{ W, F, W, W, F, W, W, W, F, W, F, W, W, W, F, W, W, F, W },
			{ W, F, F, W, F, F, F, F, F, F, F, F, F, F, F, W, F, F, W },
			{ W, W, F, W, F, W, F, W, W, W, W, W, F, W, F, W, F, W, W },
			{ W, F, F, F, F, W, F, F, F, W, F, F, F, W, F, F, F, F, W },
			{ W, F, W, W, W, W, W, W, F, W, F, W, W, W, W, W, W, F, W },
			{ W, P, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, P, W },
			{ W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W }
		};
		SetMap(Tableau, Height);
	}
	else if (GetLevel() == 2) {
		Object Tableau[Height][Width]{
			{ W, V, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, V, W },
			{ W, F, F, F, F, F, F, F, F, W, F, F, F, F, F, F, F, F, W },
			{ W, F, W, W, F, W, W, W, F, W, F, W, W, W, F, W, W, F, W },
			{ W, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, W },
			{ W, F, H, H, F, W, F, W, W, W, W, W, F, W, F, H, H, F, W },
			{ W, F, F, F, F, W, F, F, F, W, F, F, F, W, F, F, F, F, W },
			{ W, F, W, W, F, W, W, W, F, W, F, W, W, W, F, W, W, F, W },
			{ W, F, F, F, F, F, V, V, V, V, V, V, V, F, F, F, F, F, W },
			{ W, F, W, W, W, W, V, W, W, V, W, W, V, W, W, W, W, F, W },
			{ W, F, F, F, F, F, V, W, V, P, V, W, V, F, F, F, F, F, W },
			{ W, W, W, W, F, W, V, W, W, V, W, W, V, W, F, W, W, W, W },
			{ W, F, F, F, F, W, V, V, V, V, V, V, V, W, F, F, F, F, W },
			{ W, F, W, W, F, W, F, W, W, V, W, W, F, W, F, W, W, F, W },
			{ W, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, W },
			{ W, F, W, W, W, F, W, W, F, H, F, W, W, F, W, W, W, F, W },
			{ W, F, F, W, F, F, F, F, F, F, F, F, F, F, F, W, F, F, W },
			{ W, H, F, W, F, W, F, W, W, W, W, W, F, W, F, W, F, H, W },
			{ W, F, F, F, F, W, F, F, F, W, F, F, F, W, F, F, F, F, W },
			{ W, F, W, W, W, W, F, W, F, W, F, W, F, W, W, W, W, F, W },
			{ W, F, F, F, F, F, F, W, F, F, F, W, F, F, F, F, F, F, W },
			{ W, V, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, V, W }
		};
		SetMap(Tableau, Height);
	}
	else if (GetLevel() == 3) {
		Object Tableau[Height][Width]{
			{ W, W, W, W, W, W, W, W, W, F, W, W, W, W, W, W, W, W, W },
			{ W, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, W },
			{ W, F, W, W, F, W, W, W, F, H, F, W, W, W, F, W, W, F, W },
			{ W, F, F, F, F, F, F, F, F, H, F, F, F, F, F, F, F, F, W },
			{ W, F, H, H, F, H, F, H, F, W, F, H, F, H, F, H, H, F, W },
			{ W, F, F, F, H, F, F, F, F, W, F, F, F, F, H, F, F, F, W },
			{ W, H, F, H, F, F, W, W, F, H, F, W, W, F, F, H, F, H, W },
			{ W, F, F, F, F, H, F, F, F, F, F, F, F, H, F, F, F, F, W },
			{ W, F, W, W, W, W, F, H, H, V, H, H, F, W, W, W, W, F, W },
			{ W, F, F, F, F, F, F, H, V, P, V, H, F, F, F, F, F, F, W },
			{ F, F, H, H, F, W, F, H, H, V, H, H, F, W, F, H, H, F, F },
			{ W, F, F, F, F, W, F, F, F, F, F, F, F, W, F, F, F, F, W },
			{ W, F, W, W, F, W, F, H, H, F, H, H, F, W, F, W, W, F, W },
			{ W, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, W },
			{ W, F, H, F, H, F, W, W, F, H, F, W, W, F, H, F, H, F, W },
			{ W, F, F, F, H, F, F, F, F, F, F, F, F, F, H, F, F, F, W },
			{ W, H, F, H, F, H, F, W, W, F, W, W, F, H, F, H, F, H, W },
			{ W, F, F, F, F, H, F, F, F, F, F, F, F, H, F, F, F, F, W },
			{ W, F, W, F, W, F, F, W, F, H, F, W, F, F, W, F, W, F, W },
			{ W, F, F, F, F, F, H, W, F, F, F, W, H, F, F, F, F, F, W },
			{ W, W, W, W, W, W, W, W, W, F, W, W, W, W, W, W, W, W, W }
		};
		SetMap(Tableau, Height);
	}
	else if (GetLevel() == 4) {
		Object Tableau[Height][Width]{
			{ W, V, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, V, W },
			{ R, F, F, F, F, F, F, F, F, W, F, F, F, F, F, F, F, F, L },
			{ W, F, W, W, F, W, W, W, F, W, F, W, W, W, F, W, W, F, W },
			{ W, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, W },
			{ W, F, H, H, F, W, F, W, W, W, W, W, F, W, F, H, H, F, W },
			{ W, F, F, F, F, W, F, F, F, W, F, F, F, W, F, F, F, F, W },
			{ W, F, W, W, F, W, W, W, F, W, F, W, W, W, F, W, W, F, W },
			{ W, F, F, F, F, F, V, V, V, V, V, V, V, F, F, F, F, F, W },
			{ W, F, W, W, W, W, V, W, W, V, W, W, V, W, W, W, W, F, W },
			{ W, F, F, F, F, F, V, W, V, P, V, W, V, F, F, F, F, F, W },
			{ W, W, W, W, F, W, V, W, W, V, W, W, V, W, F, W, W, W, W },
			{ W, F, F, F, F, W, V, V, V, V, V, V, V, W, F, F, F, F, W },
			{ W, F, W, W, F, W, F, W, W, V, W, W, F, W, F, W, W, F, W },
			{ R, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, F, L },
			{ W, F, W, W, W, F, W, W, F, H, F, W, W, F, W, W, W, F, W },
			{ W, F, F, W, F, F, F, F, F, F, F, F, F, F, F, W, F, F, W },
			{ W, H, F, W, F, W, F, W, W, W, W, W, F, W, F, W, F, H, W },
			{ W, F, F, F, F, W, F, F, F, W, F, F, F, W, F, F, F, F, W },
			{ W, F, W, W, W, W, F, W, F, W, F, W, F, W, W, W, W, F, W },
			{ W, F, F, F, F, F, F, W, F, F, F, W, F, F, F, F, F, F, W },
			{ W, V, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, V, W }
		};
		SetMap(Tableau, Height);
	}
	//else if (GetLevel() == 5)
	//{

	//}
	else if (GetLevel() == LevelTest) {
		Object Tableau[Height][Width]{
			{ W, W, D, W, W, W, W, W, D, D, D, W, W, W, W, W, W, W, W },
			{ W, R, V, V, V, V, V, W, V, V, V, V, V, V, V, V, V, D, W },
			{ W, V, V, D, V, V, V, W, V, V, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, W, V, V, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, D, V, V, W, V, V, V, V, V, V, V, V, V, V, W },
			{ V, V, V, V, V, V, V, W, V, V, V, V, V, V, V, V, V, V, V },
			{ W, V, V, V, V, D, V, W, V, V, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, W, V, V, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, W, V, V, V, W, V, V, V, V, V, V, W },
			{ V, V, V, V, V, V, V, W, V, V, V, W, V, V, V, V, V, V, H },
			{ W, V, V, V, V, V, V, W, W, W, W, W, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, V, V, V, F, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, V, V, H, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, V, V, P, V, V, V, V, V, V, V, V, W },
			{ W, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, W },
			{ W, U, V, V, V, V, V, V, V, V, V, V, V, V, V, V, V, L, W },
			{ W, W, W, W, W, W, W, W, W, V, W, W, W, W, W, W, W, W, W }
		};
		SetMap(Tableau, Height);
	}
}
void CPacman::SetMap(const Object Map[][Width], const int& MapHeight) {
	for (int i(NULL); i < MapHeight; ++i) {
		for (int j(NULL); j < Width; ++j) {
			CCharacter Bullet;

			Map_[i][j] = Map[i][j];

			switch (Map_[i][j]) {
			case D:
			case U:
			case R:
			case L:
				Bullet.SetXBox(j);
				Bullet.SetYBox(i);
				Bullet.SetVivant(false);

				switch (Map_[i][j]) {
				case D:
					Bullet.SetDirection(D_Down);
					break;
				case U:
					Bullet.SetDirection(D_Up);
					break;
				case R:
					Bullet.SetDirection(D_Right);
					break;
				case L:
					Bullet.SetDirection(D_Left);
					break;
				}

				Bullets_.push_back(Bullet);
				break;
			}
		}
	}
}
void CPacman::SetMenu(const Menu& TheMenu) {
	switch (TheMenu) {
	case M_Main:
		SetCursor(S_Principal_Jouer);
		break;
	case M_Options:
		SetCursor(S_Options_Themes);
		break;
	case M_Themes:
		SetCursor(S_Themes_Pacman1);
		break;
	case M_Custom:
		SetCursor(S_Custom_Pacman);
		break;
	case M_CustomPacman:
		SetCursor(S_CustomPacman_Pacman1);
		break;
	case M_CustomGhosts:
		SetCursor(S_CustomGhosts_Pacman1);
		break;
	case M_CustomFood:
		SetCursor(S_CustomFood_Pacman1);
		break;
	case M_CustomPower:
		SetCursor(S_CustomPower_Pacman1);
		break;
	case M_CustomWall:
		SetCursor(S_CustomWall_Pacman1);
		break;
	case M_CustomHazard:
		SetCursor(S_CustomHazard_Pacman1);
		break;
	case M_CustomCannon:
		SetCursor(S_CustomCannon_Pacman1);
		break;
	case M_CustomBullet:
		SetCursor(S_CustomBullet_Pacman1);
		break;
	case M_Credits:
		SetCursor(S_Credits_Return);
		break;
	case M_Pause:
		SetCursor(S_Pause_Resume);
		break;
	case M_Won:
		SetCursor(S_Won_Replay);
		break;
	case M_Gameover:
		SetCursor(S_GameOver_Retry);
		break;
	}

	Menu_ = TheMenu;
}
void CPacman::SetPause(const bool& Pause) {
	if (GetMenu() != M_Won && GetMenu() != M_Gameover) {
		if (Pause)
			SetMenu(M_Pause);
		else
			SetMenu(M_None);

		Pause_ = Pause;
	}
}
void CPacman::SetPlaying(const bool& Playing) {
	Playing_ = Playing;
}
void CPacman::SetTexturePath(const std::string& TextureType, const std::string& Path) {
	TexturePaths_[TextureType] = TextureType + "/" + Path;
	SetTextures();
}
void CPacman::SetTexturePaths() {
	if (GetTheme() != T_Custom) {

		TexturePaths_["Pacman"] = "Pacman/" + ttos(GetTheme());
		TexturePaths_["Ghosts"] = "Ghosts/" + ttos(GetTheme());
		TexturePaths_["Food"] = "Food/" + ttos(GetTheme());
		TexturePaths_["Power"] = "Power/" + ttos(GetTheme());
		TexturePaths_["Wall"] = "Wall/" + ttos(GetTheme());
		TexturePaths_["Hazard"] = "Hazard/" + ttos(GetTheme());
		TexturePaths_["Cannon"] = "Cannon/" + ttos(GetTheme());
		TexturePaths_["Bullet"] = "Bullet/" + ttos(GetTheme());
	}
}
void CPacman::SetTextures() {
	// Curseurs
	Textures_["MenuCursor"] = LoadImage("Images/Misc/pacmanmenu.bmp");
	Textures_["SmallMenuCursor"] = LoadImage("Images/Misc/smallpacmanmenu.bmp");
	// CheckMark
	Textures_["CheckMark"] = LoadImage("Images/Misc/check.bmp");
	// Menus
	Textures_["Menu"] = LoadImage("Images/Menus/Menu.bmp");
	Textures_["Options"] = LoadImage("Images/Menus/options.bmp");
	Textures_["Themes"] = LoadImage("Images/Menus/Themes.bmp");
	Textures_["Custom"] = LoadImage("Images/Menus/Custom.bmp");
	Textures_["CustomPacman"] = LoadImage("Images/Menus/CustomPacman.bmp");
	Textures_["CustomGhosts"] = LoadImage("Images/Menus/CustomGhosts.bmp");
	Textures_["CustomFood"] = LoadImage("Images/Menus/CustomFood.bmp");
	Textures_["CustomPower"] = LoadImage("Images/Menus/CustomPower.bmp");
	Textures_["CustomWalls"] = LoadImage("Images/Menus/CustomWalls.bmp");
	Textures_["CustomHazard"] = LoadImage("Images/Menus/CustomHazard.bmp");
	Textures_["CustomCannon"] = LoadImage("Images/Menus/CustomCannon.bmp");
	Textures_["CustomBullet"] = LoadImage("Images/Menus/CustomBullet.bmp");
	Textures_["Credits"] = LoadImage("Images/Menus/Credits.bmp");
	// In-game menus
	Textures_["GameOver"] = LoadImage("Images/Menus/Gameover.bmp");
	Textures_["Pause"] = LoadImage("Images/Menus/Pause.bmp");
	Textures_["Won"] = LoadImage("Images/Menus/Won.bmp");
	// End of level
	Textures_["Ladder"] = LoadImage("Images/Misc/Ladder.bmp");
	Textures_["Door"] = LoadImage("Images/Misc/Door.bmp");
	// Pacman
	Textures_["PacmanRight"] = LoadImage("Images/" + TexturePaths_["Pacman"] + "pacmand.bmp");
	Textures_["ClosedPacmanRight"] = LoadImage("Images/" + TexturePaths_["Pacman"] + "pacmanfd.bmp");
	Textures_["PacmanUp"] = LoadImage("Images/" + TexturePaths_["Pacman"] + "pacmanh.bmp");
	Textures_["ClosedPacmanUp"] = LoadImage("Images/" + TexturePaths_["Pacman"] + "pacmanfh.bmp");
	Textures_["PacmanLeft"] = LoadImage("Images/" + TexturePaths_["Pacman"] + "pacmang.bmp");
	Textures_["ClosedPacmanLeft"] = LoadImage("Images/" + TexturePaths_["Pacman"] + "pacmanfg.bmp");
	Textures_["PacmanDown"] = LoadImage("Images/" + TexturePaths_["Pacman"] + "pacmanb.bmp");
	Textures_["ClosedPacmanDown"] = LoadImage("Images/" + TexturePaths_["Pacman"] + "pacmanfb.bmp");
	// Bashful
	Textures_["BashfulRight"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "bashfuld.bmp");
	Textures_["BashfulLeft"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "bashfulg.bmp");
	Textures_["BashfulDown"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "bashfulb.bmp");
	Textures_["BashfulUp"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "bashfulh.bmp");
	// Pokey
	Textures_["PokeyRight"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "pokeyd.bmp");
	Textures_["PokeyLeft"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "pokeyg.bmp");
	Textures_["PokeyDown"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "pokeyb.bmp");
	Textures_["PokeyUp"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "pokeyh.bmp");
	// Shadow
	Textures_["ShadowRight"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "shadowd.bmp");
	Textures_["ShadowLeft"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "shadowg.bmp");
	Textures_["ShadowDown"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "shadowb.bmp");
	Textures_["ShadowUp"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "shadowh.bmp");
	// Speedy
	Textures_["SpeedyRight"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "speedyd.bmp");
	Textures_["SpeedyLeft"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "speedyg.bmp");
	Textures_["SpeedyDown"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "speedyb.bmp");
	Textures_["SpeedyUp"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "speedyh.bmp");
	// Scared Ghost
	Textures_["Peur"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "peur.bmp");
	Textures_["PeurBlanc"] = LoadImage("Images/" + TexturePaths_["Ghosts"] + "peurblanc.bmp");
	// Cannon
	Textures_["CannonRight"] = LoadImage("Images/" + TexturePaths_["Cannon"] + "cannond.bmp");
	Textures_["CannonLeft"] = LoadImage("Images/" + TexturePaths_["Cannon"] + "cannong.bmp");
	Textures_["CannonDown"] = LoadImage("Images/" + TexturePaths_["Cannon"] + "cannonb.bmp");
	Textures_["CannonUp"] = LoadImage("Images/" + TexturePaths_["Cannon"] + "cannonh.bmp");
	// Frozen cannon
	Textures_["FrozenCannonRight"] = LoadImage("Images/" + TexturePaths_["Cannon"] + "fcannond.bmp");
	Textures_["FrozenCannonLeft"] = LoadImage("Images/" + TexturePaths_["Cannon"] + "fcannong.bmp");
	Textures_["FrozenCannonDown"] = LoadImage("Images/" + TexturePaths_["Cannon"] + "fcannonb.bmp");
	Textures_["FrozenCannonUp"] = LoadImage("Images/" + TexturePaths_["Cannon"] + "fcannonh.bmp");
	// Bullet
	Textures_["BulletRight"] = LoadImage("Images/" + TexturePaths_["Bullet"] + "bulletd.bmp");
	Textures_["BulletLeft"] = LoadImage("Images/" + TexturePaths_["Bullet"] + "bulletg.bmp");
	Textures_["BulletDown"] = LoadImage("Images/" + TexturePaths_["Bullet"] + "bulletb.bmp");
	Textures_["BulletUp"] = LoadImage("Images/" + TexturePaths_["Bullet"] + "bulleth.bmp");
	// Wall
	Textures_["Wall"] = LoadImage("Images/" + TexturePaths_["Wall"] + "mur.bmp");
	// Power
	Textures_["Power"] = LoadImage("Images/" + TexturePaths_["Power"] + "power.bmp");
	// Food
	Textures_["Point"] = LoadImage("Images/" + TexturePaths_["Food"] + "point.bmp");
	// Hazard
	Textures_["Hazard"] = LoadImage("Images/" + TexturePaths_["Hazard"] + "touch.bmp");
}
void CPacman::SetTheme(const Theme& TheTheme) {
	if (ttos(TheTheme) == "None")
		Theme_ = T_Pacman1;
	else
		Theme_ = TheTheme;

	switch (TheTheme) {
	case T_Pacman1:
		SetCheckMarksY(170);
		break;
	case T_Pacman2:
		SetCheckMarksY(202);
		break;
	case T_Evil:
		SetCheckMarksY(233);
		break;
	case T_Pacmario:
		SetCheckMarksY(263);
		break;
	case T_Mario:
		SetCheckMarksY(292);
		break;
	case T_Kirby:
		SetCheckMarksY(321);
		break;
	case T_Glitched:
		SetCheckMarksY(350);
		CheckMarks_["Pacman"].SetY(202);
		break;
	case T_Custom:
		CheckMarks_["Theme"].SetY(380);
		break;
	}

	SetTexturePaths();
	SetTextures();
}

// Méthodes
void CPacman::GhostWarp(CCharacter& Ghost) {
	Ghost.SetXBox(9);
	Ghost.SetYBox(9);
}
void CPacman::InitializeGame() {
	Characters_["Pacman"].SetXBox(9);
	Characters_["Pacman"].SetYBox(15);
	Characters_["Pacman"].SetDirection(D_Right);
	Characters_["Pacman"].SetVivant(true);

	Characters_["Shadow"].SetXBox(9);
	Characters_["Shadow"].SetYBox(7);

	Characters_["Bashful"].SetXBox(8);
	Characters_["Bashful"].SetYBox(9);

	Characters_["Speedy"].SetXBox(9);
	Characters_["Speedy"].SetYBox(9);

	Characters_["Pokey"].SetXBox(10);
	Characters_["Pokey"].SetYBox(9);

	SetFoodLeft(true);
	SetInvincible(false);
	SetGameOver(false);
	SetPause(false);

	SetFrame(0);
	SetFrameCannonShot(0);
	SetFrameInvincible(0);

	while (!Bullets_.empty())
		Bullets_.pop_back();

	SetLevel(GetLevel());
}
void CPacman::ManageSelection() {
	if (GetAction() == EVEntrer && GetMenu() != M_None) {
		switch (GetMenu()) {
		case M_Main:
			switch (GetCursorSelection()) {
			case S_Principal_Jouer:
				SetPlaying(true);
				SetMenu(M_None);
				break;
			case S_Principal_Options:
				SetMenu(M_Options);
				break;
			case S_Principal_Quitter:
				SetAction(EVQuit);
			}
			break;
		case M_Options:
			switch (GetCursorSelection()) {
			case S_Options_Themes:
				SetMenu(M_Themes);
				break;
			case S_Options_Credits:
				SetMenu(M_Credits);
				break;
			case S_Options_Return:
				if (!GetPause())
				{
					SetMenu(M_Main);
					SetCursor(S_Principal_Options);
				}
				else
					SetMenu(M_Pause);
			}
			break;
		case M_Themes:
			switch (GetCursorSelection()) {
			case S_Themes_Pacman1:
				SetTheme(T_Pacman1);
				break;
			case S_Themes_Pacman2:
				SetTheme(T_Pacman2);
				break;
			case S_Themes_Evil:
				SetTheme(T_Evil);
				break;
			case S_Themes_Pacmario:
				SetTheme(T_Pacmario);
				break;
			case S_Themes_Mario:
				SetTheme(T_Mario);
				break;
			case S_Themes_Kirby:
				SetTheme(T_Kirby);
				break;
			case S_Themes_Glitched:
				SetTheme(T_Glitched);
				break;
			case S_Themes_Custom:
				SetTheme(T_Custom);
				SetMenu(M_Custom);
				break;
			case S_Themes_Return:
				SetMenu(M_Options);
				break;
			}
			break;
		case M_Custom:
			switch (GetCursorSelection()) {
			case S_Custom_Pacman:
				SetMenu(M_CustomPacman);
				break;
			case S_Custom_Ghosts:
				SetMenu(M_CustomGhosts);
				break;
			case S_Custom_Food:
				SetMenu(M_CustomFood);
				break;
			case S_Custom_Power:
				SetMenu(M_CustomPower);
				break;
			case S_Custom_Walls:
				SetMenu(M_CustomWall);
				break;
			case S_Custom_Hazard:
				SetMenu(M_CustomHazard);
				break;
			case S_Custom_Cannon:
				SetMenu(M_CustomCannon);
				break;
			case S_Custom_Bullet:
				SetMenu(M_CustomBullet);
				break;
			case S_Custom_Return:
				SetMenu(M_Themes);
				SetCursor(S_Themes_Custom);
				break;
			}
			break;
		case M_CustomPacman:
			switch (GetCursorSelection()) {
			case S_CustomPacman_Pacman1:
				SetTexturePath("Pacman", "pacman1");
				CheckMarks_["Pacman"].SetY(170);
				break;
			case S_CustomPacman_Pacman2:
				SetTexturePath("Pacman", "pacman2");
				CheckMarks_["Pacman"].SetY(202);
				break;
			case S_CustomPacman_Evil:
				SetTexturePath("Pacman", "evil");
				CheckMarks_["Pacman"].SetY(233);
				break;
			case S_CustomPacman_Pacmario:
				SetTexturePath("Pacman", "pacmario");
				CheckMarks_["Pacman"].SetY(263);
				break;
			case S_CustomPacman_Mario:
				SetTexturePath("Pacman", "mario");
				CheckMarks_["Pacman"].SetY(292);
				break;
			case S_CustomPacman_Kirby:
				SetTexturePath("Pacman", "kirby");
				CheckMarks_["Pacman"].SetY(321);
				break;
			case S_CustomPacman_Return:
				SetMenu(M_Custom);
				break;
			}
			break;
		case M_CustomGhosts:
			switch (GetCursorSelection()) {
			case S_CustomGhosts_Pacman1:
				SetTexturePath("Ghosts", "pacman1");
				CheckMarks_["Ghosts"].SetY(170);
				break;
			case S_CustomGhosts_Pacman2:
				SetTexturePath("Ghosts", "pacman2");
				CheckMarks_["Ghosts"].SetY(202);
				break;
			case S_CustomGhosts_Evil:
				SetTexturePath("Ghosts", "evil");
				CheckMarks_["Ghosts"].SetY(233);
				break;
			case S_CustomGhosts_Pacmario:
				SetTexturePath("Ghosts", "pacmario");
				CheckMarks_["Ghosts"].SetY(263);
				break;
			case S_CustomGhosts_Mario:
				SetTexturePath("Ghosts", "mario");
				CheckMarks_["Ghosts"].SetY(292);
				break;
			case S_CustomGhosts_Kirby:
				SetTexturePath("Ghosts", "kirby");
				CheckMarks_["Ghosts"].SetY(321);
				break;
			case S_CustomGhosts_Return:
				SetMenu(M_Custom);
				SetCursor(S_Custom_Ghosts);
				break;
			}
			break;
		case M_CustomFood:
			switch (GetCursorSelection()) {
			case S_CustomFood_Pacman1:
				SetTexturePath("Food", "pacman1");
				CheckMarks_["Food"].SetY(170);
				break;
			case S_CustomFood_Pacman2:
				SetTexturePath("Food", "pacman2");
				CheckMarks_["Food"].SetY(202);
				break;
			case S_CustomFood_Evil:
				SetTexturePath("Food", "evil");
				CheckMarks_["Food"].SetY(233);
				break;
			case S_CustomFood_Pacmario:
				SetTexturePath("Food", "pacmario");
				CheckMarks_["Food"].SetY(263);
				break;
			case S_CustomFood_Mario:
				SetTexturePath("Food", "mario");
				CheckMarks_["Food"].SetY(292);
				break;
			case S_CustomFood_Kirby:
				SetTexturePath("Food", "kirby");
				CheckMarks_["Food"].SetY(321);
				break;
			case S_CustomFood_Return:
				SetMenu(M_Custom);
				SetCursor(S_Custom_Food);
				break;
			}
			break;
		case M_CustomPower:
			switch (GetCursorSelection()) {
			case S_CustomPower_Pacman1:
				SetTexturePath("Power", "pacman1");
				CheckMarks_["Power"].SetY(170);
				break;
			case S_CustomPower_Pacman2:
				SetTexturePath("Power", "pacman2");
				CheckMarks_["Power"].SetY(202);
				break;
			case S_CustomPower_Evil:
				SetTexturePath("Power", "evil");
				CheckMarks_["Power"].SetY(233);
				break;
			case S_CustomPower_Pacmario:
				SetTexturePath("Power", "pacmario");
				CheckMarks_["Power"].SetY(263);
				break;
			case S_CustomPower_Mario:
				SetTexturePath("Power", "mario");
				CheckMarks_["Power"].SetY(292);
				break;
			case S_CustomPower_Kirby:
				SetTexturePath("Power", "kirby");
				CheckMarks_["Power"].SetY(321);
				break;
			case S_CustomPower_Return:
				SetMenu(M_Custom);
				SetCursor(S_Custom_Power);
				break;
			}
			break;
		case M_CustomWall:
			switch (GetCursorSelection()) {
			case S_CustomWall_Pacman1:
				SetTexturePath("Wall", "pacman1");
				CheckMarks_["Wall"].SetY(170);
				break;
			case S_CustomWall_Pacman2:
				SetTexturePath("Wall", "pacman2");
				CheckMarks_["Wall"].SetY(202);
				break;
			case S_CustomWall_Evil:
				SetTexturePath("Wall", "evil");
				CheckMarks_["Wall"].SetY(233);
				break;
			case S_CustomWall_Pacmario:
				SetTexturePath("Wall", "pacmario");
				CheckMarks_["Wall"].SetY(263);
				break;
			case S_CustomWall_Mario:
				SetTexturePath("Wall", "mario");
				CheckMarks_["Wall"].SetY(292);
				break;
			case S_CustomWall_Kirby:
				SetTexturePath("Wall", "kirby");
				CheckMarks_["Wall"].SetY(321);
				break;
			case S_CustomWall_Return:
				SetMenu(M_Custom);
				SetCursor(S_Custom_Walls);
				break;
			}
			break;
		case M_CustomHazard:
			switch (GetCursorSelection()) {
			case S_CustomHazard_Pacman1:
				SetTexturePath("Hazard", "pacman1");
				CheckMarks_["Hazard"].SetY(170);
				break;
			case S_CustomHazard_Pacman2:
				SetTexturePath("Hazard", "pacman2");
				CheckMarks_["Hazard"].SetY(202);
				break;
			case S_CustomHazard_Evil:
				SetTexturePath("Hazard", "evil");
				CheckMarks_["Hazard"].SetY(233);
				break;
			case S_CustomHazard_Pacmario:
				SetTexturePath("Hazard", "pacmario");
				CheckMarks_["Hazard"].SetY(263);
				break;
			case S_CustomHazard_Mario:
				SetTexturePath("Hazard", "mario");
				CheckMarks_["Hazard"].SetY(292);
				break;
			case S_CustomHazard_Kirby:
				SetTexturePath("Hazard", "kirby");
				CheckMarks_["Hazard"].SetY(321);
				break;
			case S_CustomHazard_Return:
				SetMenu(M_Custom);
				SetCursor(S_Custom_Hazard);
				break;
			}
			break;
		case M_CustomCannon:
			switch (GetCursorSelection()) {
			case S_CustomCannon_Pacman1:
				SetTexturePath("Cannon", "pacman1");
				CheckMarks_["Cannon"].SetY(170);
				break;
			case S_CustomCannon_Pacman2:
				SetTexturePath("Cannon", "pacman2");
				CheckMarks_["Cannon"].SetY(202);
				break;
			case S_CustomCannon_Evil:
				SetTexturePath("Cannon", "evil");
				CheckMarks_["Cannon"].SetY(233);
				break;
			case S_CustomCannon_Pacmario:
				SetTexturePath("Cannon", "pacmario");
				CheckMarks_["Cannon"].SetY(263);
				break;
			case S_CustomCannon_Mario:
				SetTexturePath("Cannon", "mario");
				CheckMarks_["Cannon"].SetY(292);
				break;
			case S_CustomCannon_Kirby:
				SetTexturePath("Cannon", "kirby");
				CheckMarks_["Cannon"].SetY(321);
				break;
			case S_CustomCannon_Return:
				SetMenu(M_Custom);
				SetCursor(S_Custom_Cannon);
				break;
			}
			break;
		case M_CustomBullet:
			switch (GetCursorSelection()) {
			case S_CustomBullet_Pacman1:
				SetTexturePath("Bullet", "pacman1");
				CheckMarks_["Bullet"].SetY(170);
				break;
			case S_CustomBullet_Pacman2:
				SetTexturePath("Bullet", "pacman2");
				CheckMarks_["Bullet"].SetY(202);
				break;
			case S_CustomBullet_Evil:
				SetTexturePath("Bullet", "evil");
				CheckMarks_["Bullet"].SetY(233);
				break;
			case S_CustomBullet_Pacmario:
				SetTexturePath("Bullet", "pacmario");
				CheckMarks_["Bullet"].SetY(263);
				break;
			case S_CustomBullet_Mario:
				SetTexturePath("Bullet", "mario");
				CheckMarks_["Bullet"].SetY(292);
				break;
			case S_CustomBullet_Kirby:
				SetTexturePath("Bullet", "kirby");
				CheckMarks_["Bullet"].SetY(321);
				break;
			case S_CustomBullet_Return:
				SetMenu(M_Custom);
				SetCursor(S_Custom_Bullet);
				break;
			}
			break;
		case M_Credits:
			SetMenu(M_Options);
			SetCursor(S_Options_Credits);
			break;
		case M_Pause:
			switch (GetCursorSelection()) {
			case S_Pause_Resume:
				SetPause(false);
				break;
			case S_Pause_Options:
				SetMenu(M_Options);
				break;
			case S_Pause_Quit:
				SetAction(EVQuit);
				break;
			}
			break;
		case M_Won:
			switch (GetCursorSelection()) {
			case S_Won_Replay:
				SetLevel(1);
				InitializeGame();
				SetMenu(M_None);
				break;
			case S_Won_Menu:
				SetLevel(1);
				InitializeGame();
				SetPlaying(false);
				SetMenu(M_Main);
				break;
			case S_Won_Quit:
				SetAction(EVQuit);
				break;
			}
			break;
		case M_Gameover:
			switch (GetCursorSelection()) {
			case S_GameOver_Retry:
				InitializeGame();
				SetMenu(M_None);
				break;
			case S_GameOver_Menu:
				SetLevel(1);
				SetPlaying(false);
				InitializeGame();
				SetMenu(M_Main);
				break;
			case S_GameOver_Quit:
				SetAction(EVQuit);
				break;
			}
			break;
		}
	}
}
void CPacman::MoveCursor() {
	if (GetMenu() != M_None) {
		switch (GetMenu()) {
		case M_Main:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_Principal_Quitter)
					SetCursor(S_Principal_Jouer);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_Principal_Jouer)
					SetCursor(S_Principal_Quitter);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_Options:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_Options_Return)
					SetCursor(S_Options_Themes);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_Options_Themes)
					SetCursor(S_Options_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_Themes:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_Themes_Return)
					SetCursor(S_Themes_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_Themes_Pacman1)
					SetCursor(S_Themes_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_Custom:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_Custom_Return)
					SetCursor(S_Custom_Pacman);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_Custom_Pacman)
					SetCursor(S_Custom_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_CustomPacman:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_CustomPacman_Return)
					SetCursor(S_CustomPacman_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_CustomPacman_Pacman1)
					SetCursor(S_CustomPacman_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_CustomGhosts:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_CustomGhosts_Return)
					SetCursor(S_CustomGhosts_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_CustomGhosts_Pacman1)
					SetCursor(S_CustomGhosts_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_CustomFood:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_CustomFood_Return)
					SetCursor(S_CustomFood_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_CustomFood_Pacman1)
					SetCursor(S_CustomFood_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_CustomPower:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_CustomPower_Return)
					SetCursor(S_CustomPower_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_CustomPower_Pacman1)
					SetCursor(S_CustomPower_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_CustomWall:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_CustomWall_Return)
					SetCursor(S_CustomWall_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_CustomWall_Pacman1)
					SetCursor(S_CustomWall_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_CustomHazard:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_CustomHazard_Return)
					SetCursor(S_CustomHazard_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_CustomHazard_Pacman1)
					SetCursor(S_CustomHazard_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_CustomCannon:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_CustomCannon_Return)
					SetCursor(S_CustomCannon_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_CustomCannon_Pacman1)
					SetCursor(S_CustomCannon_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_CustomBullet:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_CustomBullet_Return)
					SetCursor(S_CustomBullet_Pacman1);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_CustomBullet_Pacman1)
					SetCursor(S_CustomBullet_Return);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_Pause:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_Pause_Quit)
					SetCursor(S_Pause_Resume);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_Pause_Resume)
					SetCursor(S_Pause_Quit);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_Won:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_Won_Quit)
					SetCursor(S_Won_Replay);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_Won_Replay)
					SetCursor(S_Won_Quit);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		case M_Gameover:
			switch (GetAction()) {
			case EVRight:
			case EVDown:
				if (GetCursorSelection() == S_GameOver_Quit)
					SetCursor(S_GameOver_Retry);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() + 1)));
				break;
			case EVLeft:
			case EVUp:
				if (GetCursorSelection() == S_GameOver_Retry)
					SetCursor(S_GameOver_Quit);
				else
					SetCursor(static_cast<Selection>(static_cast<int>(GetCursorSelection() - 1)));
				break;
			}
			break;
		}
	}
}
void CPacman::Play() {
	FillWindow(0, 0, 0);
	SetAction(ReadEvent());

	if (!GetPlaying() || (GetPause() && GetMenu() != M_Pause))
		ShowMenu();
	else {
		ShowGame();

		if (GetMenu() == M_None) {
			if (!GetGameOver() && !GetFoodLeft() && !GetPause()) {
				Characters_["Pacman"].GererDeplacements(GetAction(), Map_, Height);
				SetFrame(GetFrame() + 1);

				switch (GetLevel()) {
				case 1:
				case 5:
					if (Characters_["Pacman"].GetXBox() == 0 && Characters_["Pacman"].GetYBox() == 9)
					{
						InitializeGame();
						SetPlaying(false);
						SetMenu(M_Main);
					}
					else if (Characters_["Pacman"].GetXBox() == 18 && Characters_["Pacman"].GetYBox() == 9)
					{
						SetLevel(GetLevel() + 1);
						InitializeGame();
					}
					break;
				case 2:
				case 4:
					if (Characters_["Pacman"].GetXBox() == 1 && Characters_["Pacman"].GetYBox() == 20)
					{
						InitializeGame();
						SetPlaying(false);
						SetMenu(M_Main);
					}
					else if (Characters_["Pacman"].GetXBox() == 17 && Characters_["Pacman"].GetYBox() == 0)
					{
						SetLevel(GetLevel() + 1);
						InitializeGame();
					}
					break;
				case 3:
					if (Characters_["Pacman"].GetXBox() == 0 && Characters_["Pacman"].GetYBox() == 10)
					{
						InitializeGame();
						SetPlaying(false);
						SetMenu(M_Main);
					}
					else if (Characters_["Pacman"].GetXBox() == 18 && Characters_["Pacman"].GetYBox() == 10)
					{
						SetLevel(GetLevel() + 1);
						InitializeGame();
					}
					break;
				}
			}
			else {
				SetInvincible(GetFrameInvincible() > 0 && GetFrameInvincible() < 150);

				Characters_["Pacman"].GererDeplacements(GetAction(), Map_, Height);

				SetGameOver();

				if (Map_[Characters_["Pacman"].GetYBox()][Characters_["Pacman"].GetXBox()] == P) {
					SetInvincible(true);
					SetFrameInvincible(0);
				}

				Map_[Characters_["Pacman"].GetYBox()][Characters_["Pacman"].GetXBox()] = V;

				SetFrame(GetFrame() + 1);

				if (GetFrame() + 1 == GhostSpeed && !GetInvincible()) {
					Characters_["Bashful"].SePromener(Map_, Height);
					Characters_["Pokey"].SePromener(Map_, Height);
					Characters_["Shadow"].Chasser(Characters_["Pacman"], Map_, Height);
					Characters_["Speedy"].Chasser(Characters_["Pacman"], Map_, Height);
					SetGameOver();
				}
				else if (GetFrame() + 1 == GhostSpeed && GetInvincible()) {
					Characters_["Bashful"].Fuir(Characters_["Pacman"], Map_, Height);
					Characters_["Pokey"].Fuir(Characters_["Pacman"], Map_, Height);
					Characters_["Shadow"].Fuir(Characters_["Pacman"], Map_, Height);
					Characters_["Speedy"].Fuir(Characters_["Pacman"], Map_, Height);
				}

				if (GetInvincible()) {
					if (Characters_["Pacman"] == Characters_["Shadow"])
						GhostWarp(Characters_["Shadow"]);
					if (Characters_["Pacman"] == Characters_["Bashful"])
						GhostWarp(Characters_["Bashful"]);
					if (Characters_["Pacman"] == Characters_["Speedy"])
						GhostWarp(Characters_["Speedy"]);
					if (Characters_["Pacman"] == Characters_["Pokey"])
						GhostWarp(Characters_["Pokey"]);
				}
			}
		}
	}
}
void CPacman::ShowGame() {
	bool AllBulletsDown(true);
	SetFoodLeft(false);

	// Afficher la carte
	for (int i(0); i < Height; ++i) {
		for (int j(0); j < Width; ++j) {
			CCharacter Bullet(0, 0);
			switch (Map_[i][j]) {
			case W:
				ShowImage(Textures_["Wall"], j * PixelsPerBox, i * PixelsPerBox);
				break;
			case F:
				ShowImage(Textures_["Point"], j * PixelsPerBox, i * PixelsPerBox);
				if (!GetFoodLeft())
					SetFoodLeft(true);
				break;
			case P:
				ShowImage(Textures_["Power"], j * PixelsPerBox, i * PixelsPerBox);
				if (!GetFoodLeft())
					SetFoodLeft(true);
				break;
			case H:
				ShowImage(Textures_["Hazard"], j * PixelsPerBox, i * PixelsPerBox);
				break;
			case D:
				if (GetInvincible())
					ShowImage(Textures_["FrozenCannonDown"], j * PixelsPerBox, i * PixelsPerBox);
				else
					ShowImage(Textures_["CannonDown"], j * PixelsPerBox, i * PixelsPerBox);
				break;
			case R:
				if (GetInvincible())
					ShowImage(Textures_["FrozenCannonRight"], j * PixelsPerBox, i * PixelsPerBox);
				else
					ShowImage(Textures_["CannonRight"], j * PixelsPerBox, i * PixelsPerBox);
				break;
			case L:
				if (GetInvincible())
					ShowImage(Textures_["FrozenCannonLeft"], j * PixelsPerBox, i * PixelsPerBox);
				else
					ShowImage(Textures_["CannonLeft"], j * PixelsPerBox, i * PixelsPerBox);
				break;
			case U:
				if (GetInvincible())
					ShowImage(Textures_["FrozenCannonUp"], j * PixelsPerBox, i * PixelsPerBox);
				else
					ShowImage(Textures_["CannonUp"], j * PixelsPerBox, i * PixelsPerBox);
				break;
			}
		}
	}

	// Afficher PacMan
	if (GetFrame() < GhostSpeed / 2) {
		switch (Characters_["Pacman"].GetDirection()) {
		case D_Right:
			ShowImage(Textures_["PacmanRight"], Characters_["Pacman"].GetX(), Characters_["Pacman"].GetY());
			break;
		case D_Left:
			ShowImage(Textures_["PacmanLeft"], Characters_["Pacman"].GetX(), Characters_["Pacman"].GetY());
			break;
		case D_Up:
			ShowImage(Textures_["PacmanUp"], Characters_["Pacman"].GetX(), Characters_["Pacman"].GetY());
			break;
		case D_Down:
			ShowImage(Textures_["PacmanDown"], Characters_["Pacman"].GetX(), Characters_["Pacman"].GetY());
			break;
		}
	}
	else {
		switch (Characters_["Pacman"].GetDirection()) {
		case D_Right:
			ShowImage(Textures_["ClosedPacmanRight"], Characters_["Pacman"].GetX(), Characters_["Pacman"].GetY());
			break;
		case D_Left:
			ShowImage(Textures_["ClosedPacmanLeft"], Characters_["Pacman"].GetX(), Characters_["Pacman"].GetY());
			break;
		case D_Up:
			ShowImage(Textures_["ClosedPacmanUp"], Characters_["Pacman"].GetX(), Characters_["Pacman"].GetY());
			break;
		case D_Down:
			ShowImage(Textures_["ClosedPacmanDown"], Characters_["Pacman"].GetX(), Characters_["Pacman"].GetY());
			break;
		}
	}

	// Afficher les fantomes et les projectiles
	if (GetFoodLeft()) {
		if (!GetInvincible()) {
			// Vérifier si tous les projectiles ont atteint un obstacle
			for (unsigned int i(0); i < Bullets_.size() && AllBulletsDown; ++i)
				AllBulletsDown = !Bullets_[i].GetVivant();
			// Tirer un projectile ou le faire avancer
			if (GetFrameCannonShot() == CannonSpeed && AllBulletsDown) {
				for (unsigned int i(0); i < Bullets_.size(); ++i) {
					Bullets_[i].SetVivant(true);
					Bullets_[i].Deplacer(Bullets_[i].GetDirection());

					if (Bullets_[i].GetDirection() == D_Up)
						ShowImage(Textures_["BulletUp"], Bullets_[i].GetX(), Bullets_[i].GetY());
					else if (Bullets_[i].GetDirection() == D_Down)
						ShowImage(Textures_["BulletDown"], Bullets_[i].GetX(), Bullets_[i].GetY());
					else if (Bullets_[i].GetDirection() == D_Right)
						ShowImage(Textures_["BulletRight"], Bullets_[i].GetX(), Bullets_[i].GetY());
					else if (Bullets_[i].GetDirection() == D_Left)
						ShowImage(Textures_["BulletLeft"], Bullets_[i].GetX(), Bullets_[i].GetY());

					if (Bullets_[i] == Characters_["Bashful"]) {
						Bullets_[i].SetVivant(false);
						GhostWarp(Characters_["Bashful"]);
					}
					if (Bullets_[i] == Characters_["Pokey"]) {
						Bullets_[i].SetVivant(false);
						GhostWarp(Characters_["Pokey"]);
					}
					if (Bullets_[i] == Characters_["Speedy"]) {
						Bullets_[i].SetVivant(false);
						GhostWarp(Characters_["Speedy"]);
					}
					if (Bullets_[i] == Characters_["Shadow"]) {
						Bullets_[i].SetVivant(false);
						GhostWarp(Characters_["Shadow"]);
					}
				}
			}
			// Afficher les fantomes
			switch (Characters_["Shadow"].GetDirection()) {
			case D_None:
			case D_Right:
				ShowImage(Textures_["ShadowRight"], Characters_["Shadow"].GetX(), Characters_["Shadow"].GetY());
				break;
			case D_Left:
				ShowImage(Textures_["ShadowLeft"], Characters_["Shadow"].GetX(), Characters_["Shadow"].GetY());
				break;
			case D_Down:
				ShowImage(Textures_["ShadowDown"], Characters_["Shadow"].GetX(), Characters_["Shadow"].GetY());
				break;
			case D_Up:
				ShowImage(Textures_["ShadowUp"], Characters_["Shadow"].GetX(), Characters_["Shadow"].GetY());
				break;
			}
			switch (Characters_["Bashful"].GetDirection()) {
			case D_None:
			case D_Right:
				ShowImage(Textures_["BashfulRight"], Characters_["Bashful"].GetX(), Characters_["Bashful"].GetY());
				break;
			case D_Left:
				ShowImage(Textures_["BashfulLeft"], Characters_["Bashful"].GetX(), Characters_["Bashful"].GetY());
				break;
			case D_Down:
				ShowImage(Textures_["BashfulDown"], Characters_["Bashful"].GetX(), Characters_["Bashful"].GetY());
				break;
			case D_Up:
				ShowImage(Textures_["BashfulUp"], Characters_["Bashful"].GetX(), Characters_["Bashful"].GetY());
				break;
			}
			switch (Characters_["Pokey"].GetDirection()) {
			case D_None:
			case D_Right:
				ShowImage(Textures_["PokeyRight"], Characters_["Pokey"].GetX(), Characters_["Pokey"].GetY());
				break;
			case D_Left:
				ShowImage(Textures_["PokeyLeft"], Characters_["Pokey"].GetX(), Characters_["Pokey"].GetY());
				break;
			case D_Down:
				ShowImage(Textures_["PokeyDown"], Characters_["Pokey"].GetX(), Characters_["Pokey"].GetY());
				break;
			case D_Up:
				ShowImage(Textures_["PokeyUp"], Characters_["Pokey"].GetX(), Characters_["Pokey"].GetY());
				break;
			}
			switch (Characters_["Speedy"].GetDirection()) {
			case D_None:
			case D_Right:
				ShowImage(Textures_["SpeedyRight"], Characters_["Speedy"].GetX(), Characters_["Speedy"].GetY());
				break;
			case D_Left:
				ShowImage(Textures_["SpeedyLeft"], Characters_["Speedy"].GetX(), Characters_["Speedy"].GetY());
				break;
			case D_Down:
				ShowImage(Textures_["SpeedyDown"], Characters_["Speedy"].GetX(), Characters_["Speedy"].GetY());
				break;
			case D_Up:
				ShowImage(Textures_["SpeedyUp"], Characters_["Speedy"].GetX(), Characters_["Speedy"].GetY());
				break;
			}
		}
		else {
			if (GetFrameInvincible() < 130 || GetFrameInvincible() % 10 > 4) {
				ShowImage(Textures_["Peur"], Characters_["Shadow"].GetX(), Characters_["Shadow"].GetY());
				ShowImage(Textures_["Peur"], Characters_["Bashful"].GetX(), Characters_["Bashful"].GetY());
				ShowImage(Textures_["Peur"], Characters_["Speedy"].GetX(), Characters_["Speedy"].GetY());
				ShowImage(Textures_["Peur"], Characters_["Pokey"].GetX(), Characters_["Pokey"].GetY());
			}
			else {
				ShowImage(Textures_["PeurBlanc"], Characters_["Shadow"].GetX(), Characters_["Shadow"].GetY());
				ShowImage(Textures_["PeurBlanc"], Characters_["Bashful"].GetX(), Characters_["Bashful"].GetY());
				ShowImage(Textures_["PeurBlanc"], Characters_["Speedy"].GetX(), Characters_["Speedy"].GetY());
				ShowImage(Textures_["PeurBlanc"], Characters_["Pokey"].GetX(), Characters_["Pokey"].GetY());
			}
		}
		if (!AllBulletsDown) {
			for (unsigned int i(0); i < Bullets_.size(); ++i) {
				if (Bullets_[i].GetVivant()) {
					switch (Bullets_[i].GetDirection()) {
					case D_Right:
						Bullets_[i].SetVivant(Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox() + 1] == V ||
							Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox() + 1] == F ||
							Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox() + 1] == P);
						break;
					case D_Left:
						Bullets_[i].SetVivant(Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox() - 1] == V ||
							Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox() - 1] == F ||
							Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox() - 1] == P);
						break;
					case D_Down:
						Bullets_[i].SetVivant(Map_[Bullets_[i].GetYBox() + 1][Bullets_[i].GetXBox()] == V ||
							Map_[Bullets_[i].GetYBox() + 1][Bullets_[i].GetXBox()] == F ||
							Map_[Bullets_[i].GetYBox() + 1][Bullets_[i].GetXBox()] == P);
						break;
					case D_Up:
						Bullets_[i].SetVivant(Map_[Bullets_[i].GetYBox() - 1][Bullets_[i].GetXBox()] == V ||
							Map_[Bullets_[i].GetYBox() - 1][Bullets_[i].GetXBox()] == F ||
							Map_[Bullets_[i].GetYBox() - 1][Bullets_[i].GetXBox()] == P);
						break;
					}

					if (Bullets_[i].GetVivant()) {

						switch (Bullets_[i].GetDirection()) {
						case D_Right:
							if (GetMenu() == M_None)
								Bullets_[i].DeplacerDroite();
							ShowImage(Textures_["BulletRight"], Bullets_[i].GetX(), Bullets_[i].GetY());
							break;
						case D_Left:
							if (GetMenu() == M_None)
								Bullets_[i].DeplacerGauche();
							ShowImage(Textures_["BulletLeft"], Bullets_[i].GetX(), Bullets_[i].GetY());
							break;
						case D_Down:
							if (GetMenu() == M_None)
								Bullets_[i].DeplacerBas();
							ShowImage(Textures_["BulletDown"], Bullets_[i].GetX(), Bullets_[i].GetY());
							break;
						case D_Up:
							if (GetMenu() == M_None)
								Bullets_[i].DeplacerHaut();
							ShowImage(Textures_["BulletUp"], Bullets_[i].GetX(), Bullets_[i].GetY());
							break;
						}

						if (Bullets_[i] == Characters_["Bashful"]) {
							Bullets_[i].SetVivant(false);
							GhostWarp(Characters_["Bashful"]);
						}
						if (Bullets_[i] == Characters_["Pokey"]) {
							Bullets_[i].SetVivant(false);
							GhostWarp(Characters_["Pokey"]);
						}
						if (Bullets_[i] == Characters_["Speedy"]) {
							Bullets_[i].SetVivant(false);
							GhostWarp(Characters_["Speedy"]);
						}
						if (Bullets_[i] == Characters_["Shadow"]) {
							Bullets_[i].SetVivant(false);
							GhostWarp(Characters_["Shadow"]);
						}
					}
					if (!Bullets_[i].GetVivant()) {
						switch (Bullets_[i].GetDirection()) {
						case D_Right:
							while (Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox()] != R)
								Bullets_[i].DeplacerGauche();
							break;
						case D_Left:
							while (Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox()] != L)
								Bullets_[i].DeplacerDroite();
							break;
						case D_Down:
							while (Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox()] != D)
								Bullets_[i].DeplacerHaut();
							break;
						case D_Up:
							while (Map_[Bullets_[i].GetYBox()][Bullets_[i].GetXBox()] != U)
								Bullets_[i].DeplacerBas();
							break;
						}
						Bullets_[i].SetDirection(OppositeDirection(Bullets_[i].GetDirection()));
					}
				}
			}
		}
	}
	else if (GetLevel() != LevelLast && GetLevel() != LevelTest)
		ShowLevelEnd();
	else if (GetMenu() == M_None)
		SetMenu(M_Won);

	// Afficher les in-game menus
	if (GetMenu() != M_None)
		ShowMenu();

	// Rafraichir la fenetre
	RefreshWindow();

	// Attendre 30ms pour ralentir le jeu (délai à ajuster si nécessaire)
	Wait(30);
}
void CPacman::ShowLevelEnd() {
	if (GetLevel() == 1 || GetLevel() == 5) {
		ShowImage(Textures_["Door"], 0, 9 * PixelsPerBox);
		ShowImage(Textures_["Ladder"], 18 * PixelsPerBox, 9 * PixelsPerBox);
	}
	else if (GetLevel() == 2 || GetLevel() == 4) {
		ShowImage(Textures_["Door"], PixelsPerBox, 20 * PixelsPerBox);
		ShowImage(Textures_["Ladder"], 17 * PixelsPerBox, 0);
	}
	else if (GetLevel() == 3) {
		ShowImage(Textures_["Door"], 0, 10 * PixelsPerBox);
		ShowImage(Textures_["Ladder"], 18 * PixelsPerBox, 10 * PixelsPerBox);
	}
	RefreshWindow();
}
void CPacman::ShowMenu() {
	MoveCursor();
	ManageSelection();

	if (GetMenu() != M_None) {
		// Afficher le menu dans lequel on se trouve
		if (GetMenu() == M_Pause || GetMenu() == M_Gameover || GetMenu() == M_Won)
			ShowImage(Textures_[mtos(GetMenu())], 128, 127);
		else
			ShowImage(Textures_[mtos(GetMenu())], 0, 0);

		// Afficher le curseur (ou le petit curseur)
		if (!(GetMenu() == M_Main || GetMenu() == M_Options || GetMenu() == M_Credits)) {
			switch (GetMenu()) {
			case M_Themes:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Theme"].GetX(), CheckMarks_["Theme"].GetY());
				break;
			case M_CustomPacman:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Pacman"].GetX(), CheckMarks_["Pacman"].GetY());
				break;
			case M_CustomGhosts:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Ghosts"].GetX(), CheckMarks_["Ghosts"].GetY());
				break;
			case M_CustomFood:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Food"].GetX(), CheckMarks_["Food"].GetY());
				break;
			case M_CustomPower:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Power"].GetX(), CheckMarks_["Power"].GetY());
				break;
			case M_CustomWall:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Wall"].GetX(), CheckMarks_["Wall"].GetY());
				break;
			case M_CustomHazard:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Hazard"].GetX(), CheckMarks_["Hazard"].GetY());
				break;
			case M_CustomCannon:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Cannon"].GetX(), CheckMarks_["Cannon"].GetY());
				break;
			case M_CustomBullet:
				ShowImage(Textures_["CheckMark"], CheckMarks_["Bullet"].GetX(), CheckMarks_["Bullet"].GetY());
				break;
			}

			ShowImage(Textures_["SmallMenuCursor"], Cursor_.GetX(), Cursor_.GetY());
		}
		else
			ShowImage(Textures_["MenuCursor"], Cursor_.GetX(), Cursor_.GetY());

		RefreshWindow();
	}
}

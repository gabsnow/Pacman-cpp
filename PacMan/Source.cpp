// Pacman.cpp
// Fait par Gabriel Bourgeois le 28 Novembre 2017
// Jeu de pacman <3

#include "sdlclg.h"
#include "PacmanGame.h"
#include <ctime>
#include <cstdlib>
using namespace std;

int main(int argc, char *argv[]){
	srand(static_cast<unsigned int>(time(NULL)));
	CPacman Game;

	while(Game.GetAction() != EVQuit){
		Game.Play();
	}

	return 0;
}
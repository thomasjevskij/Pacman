#include "Global.hpp"
#include "PacmanGame.hpp"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE previousInstance, LPSTR commandLine, int showState)
{
	PacmanGame game(instance);
	return game.Start();
}
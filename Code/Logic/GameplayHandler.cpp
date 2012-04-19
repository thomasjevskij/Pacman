#include "GamePlayHandler.hpp"

namespace Model
{
	void GameplayHandler::Initialize()
	{
		//Levelhandler loading
	}
	void GameplayHandler::Update(){}
	//GameObject GameplayHandler::GetPacman()
	//vector<GameObject> GameplayHandler::GetGhost()
	//vector<Coord> GameplayHandler::GetPellets()
	//vector<Coord> GameplayHandler::GetPowerPellets()
	Level GameplayHandler::GetLevel()
	{
		return level;
	}

	int GameplayHandler::GetCurrentlevelIndex()
	{
		return currentLevel;
	}

	int GameplayHandler::GetLives()
	{
		return lives;
	}
	int GameplayHandler::GetScore()
	{
		return score;
	}
	//Time GameplayHandler::GetTimeLeft()

}
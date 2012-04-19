#include "GameplayHandler.hpp"

namespace Model
{
	GameplayHandler::GameplayHandler()
	{
		mLevel = mLevelHandler.GetCurrentLevel();
	}

	void GameplayHandler::Update()
	{
		//Update movement
		//test collision
		// Modify level acordingly
		// Report Events
	}


	bool GameplayHandler::TestGridCollision(Coord objectPos1, Coord objectPos2)
	{
		return (objectPos1 == objectPos2);
	}
	bool GameplayHandler::TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos){}
	


	//GameObject GameplayHandler::GetPacman()
	//vector<GameObject> GameplayHandler::GetGhosts()


	Level GameplayHandler::GetLevel()
	{
		return mLevel;
	}

	int GameplayHandler::GetCurrentlevelIndex()
	{
		return mCurrentLevel;
	}

	int GameplayHandler::GetLives()
	{
		return mLives;
	}
	int GameplayHandler::GetScore()
	{
		return mScore;
	}
	//Time GameplayHandler::GetTimeLeft()

}
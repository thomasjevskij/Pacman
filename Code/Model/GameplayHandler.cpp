
#include "GameplayHandler.hpp"

namespace Model
{
	GameplayHandler::GameplayHandler(): mPlayer(Coord(1,1))
	{
		mGameRestart = true;
	}

	void GameplayHandler::Update(float dt)
	{
		//Test if it should to load the next level
		if (mLevelWasWon = true)
			NewLevel();
		//Test if it should start a new game
		if (mGameRestart = true)
			ResetGame();

		//Update movement
		mPlayer.UpdateMovement(&mLevel);
		for each( Ghost g in mGhosts)
			g.UpdateMovement(mPlayer.GetRealPos());

		//

		//Test if Pacman is eating anything
		if (mLevel.GetCell(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y).Type == Cell::C_CELLTYPE_PELLET)
		{
			mScore += 10;
			//notify view and check if fruit should be added
			mLevel.SetEaten(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y);
		}
		else if (mLevel.GetCell(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y).Type == Cell::C_CELLTYPE_POWERPELLET)
		{
			mScore += 50;
			//start powermode, notify view and check if fruit should be added
			mLevel.SetEaten(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y);
		}
		else if (mLevel.GetCell(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y).Type == Cell::C_CELLTYPE_FOOD)
		{
			mScore += mCurrentLevel * 100;
			//remove fruitobject
			mLevel.RemoveFood();
		}

		//Check if fruittimer has ended

		//Test if Pacman collides with ghosts
		for each (Ghost g in mGhosts)
		{
			if (TestRealCollision(g.GetRealPos(),mPlayer.GetRealPos()))
			{
				if(g.GetGhostState() == g.Chase || g.GetGhostState() == g.Scatter)
				{
					//Kill Pacman, end game etc
					mGameRestart = true;
				}
				else if(g.GetGhostState() == g.Frightened)
				{
					// Kill Ghost, add points
					g.SetGhostState(g.Killed);
				}
			}
		}

		//Update movement
		//test collision
		// -Modify level acordingly
		// -Report Events
	}


	bool GameplayHandler::TestGridCollision(Coord objectPos1, Coord objectPos2)
	{
		return (objectPos1 == objectPos2);
	}
	bool GameplayHandler::TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos){ return true;}
	


	GameObject GameplayHandler::GetPacman()
	{
		return mPlayer;
	}

	std::vector<Ghost> GameplayHandler::GetGhosts()
	{
		return mGhosts;
	}


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

	void GameplayHandler::NewLevel()
	{
		mLevelHandler.SetCurrentLevelIndex(mLevelHandler.GetCurrentLevelIndex() + 1);
		mLevel = mLevelHandler.GetCurrentLevel();
		mCurrentLevel = mLevelHandler.GetCurrentLevelIndex() +1;
		mLevelWasWon = false; 
		//todo: Reset pacman and ghost positions
	}
	void GameplayHandler::ResetGame()
	{
		mLevelHandler.SetCurrentLevelIndex(0);
		mLevel = mLevelHandler.GetCurrentLevel();
		mCurrentLevel = mLevelHandler.GetCurrentLevelIndex() +1;
		mScore = 0;
		mLives = 3;
		mGameRestart = false;
		//todo: Reset or make new player and ghosts
	}


}
#include "GameplayHandler.hpp"

namespace Model
{
	GameplayHandler::GameplayHandler(): mPlayer(Coord(1,1)), mFruit()
	{
		mGameRestart = true;
		srand(NULL);
	}

	void GameplayHandler::Update(float dt)
	{
		mGameTime += dt;

		//Test if it should to load the next level
		if (mLevelWasWon = true)
			NewLevel();

		//Test if it should start a new game
		if (mGameRestart = true)
			ResetGame();

		//Update movement
		mPlayer.UpdateMovement(&mLevel, dt);
		for each( Ghost g in mGhosts)
		{
			g.GhostStateBehaviour(mGameTime,mCurrentLevel);
			g.UpdateMovement(mPlayer.GetGridPosition(), dt, &mLevel, &mPlayer, mGhosts[0].GetGridPosition());
		}

		//Test if Pacman is eating anything
		Coord playerPos = mPlayer.GetGridPosition();
		if (mLevel.GetCell(playerPos.X, playerPos.Y).Type == Cell::C_CELLTYPE_PELLET)
		{
			mScore += 10;
			mPelletsEaten++;
			if (mPelletsEaten == 70 || mPelletsEaten == 170)
				mFruit = Fruit();
			mLevel.SetEaten(playerPos.X, playerPos.Y);
			mGameEventSubscriber->PelletEaten(playerPos);
		}
		else if (mLevel.GetCell(playerPos.X, playerPos.Y).Type == Cell::C_CELLTYPE_POWERPELLET)
		{
			mScore += 50;
			mPelletsEaten++;
			if (mPelletsEaten == 70 || mPelletsEaten == 170)
				mFruit = Fruit();
			
			for each (Ghost c in mGhosts)
				c.SetGhostState(c.Frightened);
			mLevel.SetEaten(playerPos.X, playerPos.Y);
			mGameEventSubscriber->PowerPelletEaten(playerPos);
		}
		else if (mLevel.GetCell(playerPos.X, playerPos.Y).Type == Cell::C_CELLTYPE_FOOD)
		{
			mScore += mCurrentLevel * 100;
			mLevel.RemoveFood();
		}

		//Check if fruitlifetime has ended
		if (mLevel.FoodExists() == true)
		{
			if (mFruit.IsLifeTimeOver(dt) == true)
			{
				mLevel.RemoveFood();
			}
		}

		//Test if Pacman collides with ghosts
		for each (Ghost g in mGhosts)
		{
			if (TestRealCollision(g.GetRealPos(),mPlayer.GetGridPosition()))
			{
				if(g.GetGhostState() == g.Chase || g.GetGhostState() == g.Scatter)
				{
					mGameEventSubscriber->PacmanKilled();
					mGameRestart = true;
				}
				else if(g.GetGhostState() == g.Frightened)
				{
					g.SetGhostState(g.Killed);
					int k = 0;
					for each (Ghost c in mGhosts)
						if (c.GetGhostState() == c.Killed)
							k++;
					mScore += 200 * k;
				}
			}
		}
	}


	bool GameplayHandler::TestGridCollision(Coord objectPos1, Coord objectPos2)
	{
		return (objectPos1 == objectPos2);
	}
	bool GameplayHandler::TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos)
	{ 
		if(sqrt(pow((ghostRealPos.X - pacmanRealPos.X),2) + pow((ghostRealPos.Y - pacmanRealPos.Y),2)) < 40)
			return true;
		return false;
	}
	
	Player GameplayHandler::GetPacman() const
	{
		return mPlayer;
	}

	std::vector<Ghost> GameplayHandler::GetGhosts() const
	{
		return mGhosts;
	}

	Level GameplayHandler::GetLevel() const
	{
		return mLevel;
	}

	int GameplayHandler::GetCurrentlevelIndex() const
	{
		return mCurrentLevel;
	}

	int GameplayHandler::GetLives() const
	{
		return mLives;
	}
	int GameplayHandler::GetScore() const
	{
		return mScore;
	}
	float GameplayHandler::GetTimeLeft() const
	{
		return mGameTime;
	}

	void GameplayHandler::NewLevel()
	{
		mLevelHandler.SetCurrentLevelIndex(mLevelHandler.GetCurrentLevelIndex() + 1);
		mLevel = mLevelHandler.GetCurrentLevel();
		mCurrentLevel = mLevelHandler.GetCurrentLevelIndex() +1;
		mGhosts.clear();
		for (int i = 0; i<=3; i++)
			mGhosts.push_back(Ghost(mLevel.GetGhostSpawnPositions()[i], i));
		mPlayer = Player(mLevel.GetPacmanSpawnPosition());
		mLevelWasWon = false;
		mPelletsEaten = 0;
	}

	void GameplayHandler::ResetGame()
	{
		mLevelHandler.SetCurrentLevelIndex(0);
		mLevel = mLevelHandler.GetCurrentLevel();
		mCurrentLevel = mLevelHandler.GetCurrentLevelIndex() +1;
		mGhosts.clear();
		for (int i = 0; i<=3; i++)
			mGhosts.push_back(Ghost(mLevel.GetGhostSpawnPositions()[i], i));
		mPlayer = Player(mLevel.GetPacmanSpawnPosition());
		mScore = 0;
		mLives = 3;
		mGameRestart = false;
		mPelletsEaten = 0;
	}


}
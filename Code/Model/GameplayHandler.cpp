#include "GameplayHandler.hpp"

namespace Model
{
	GameplayHandler::GameplayHandler(): mPlayer(Coord(1,1)), mFruit()
	{
		mGameRestart = true;
		srand(NULL);

		//Testing message
		OutputDebugString("--Model Testing--:  Gameplayhandler initiated \n");
	}

	void GameplayHandler::Update(float dt)
	{
		
		//Testing message
		OutputDebugString("--Model Testing--:  Update() function called \n");
		
		//Test if it should start a new game
		if (mGameRestart == true)
			ResetGame();

		//Test if it should to load the next level
		if (mLevelWasWon == true)
			NewLevel();

		
		mGameTime += dt;

		//Update Powermode timer
		if(mPowerModeTimer != 0)
		{
			mPowerModeTimer += dt;
			if(mPowerModeTimer > 9)
			{
				for each (Ghost c in mGhosts)
					c.SetGhostState(c.Chase);
				mPowerModeTimer = 0;
				//mGameEventSubscriber->PowerPelletEnd();
			}
		}

		//Update movement
		mPlayer.UpdateMovement(&mLevelHandler.GetCurrentLevel(), dt);
		for(int s = 0; s < mGhosts.size(); s++)
		{
			mGhosts[s].GhostStateBehaviour(mGameTime,mCurrentLevel);
			mGhosts[s].UpdateMovement(mPlayer.GetGridPosition(), dt, &mLevelHandler.GetCurrentLevel(), &mPlayer, mGhosts[0].GetGridPosition());
		}
		//Test if Pacman is eating anything
		Coord playerPos = mPlayer.GetGridPosition();
		if (mLevelHandler.GetCurrentLevel().GetCell(playerPos.X, playerPos.Y).Type == Cell::C_CELLTYPE_PELLET)
		{
			mScore += 10;
			mPelletsEaten++;
			if (mPelletsEaten == 70 || mPelletsEaten == 170)
				mFruit = Fruit();
			mLevelHandler.GetCurrentLevel().SetEaten(playerPos.X, playerPos.Y);
			//mGameEventSubscriber->PelletEaten(playerPos);
		}
		else if (mLevelHandler.GetCurrentLevel().GetCell(playerPos.X, playerPos.Y).Type == Cell::C_CELLTYPE_POWERPELLET)
		{
			mScore += 50;
			mPowerModeTimer = dt;
			mPelletsEaten++;
			if (mPelletsEaten == 70 || mPelletsEaten == 170)
				mFruit = Fruit();
			for each (Ghost c in mGhosts)
				c.SetGhostState(c.Frightened);
			mLevelHandler.GetCurrentLevel().SetEaten(playerPos.X, playerPos.Y);
			//mGameEventSubscriber->PowerPelletEaten(playerPos);
		}
		else if (mLevelHandler.GetCurrentLevel().GetCell(playerPos.X, playerPos.Y).Type == Cell::C_CELLTYPE_FOOD)
		{
			mScore += mCurrentLevel * 100;
			mLevelHandler.GetCurrentLevel().RemoveFood();
		}

		//Check if fruitlifetime has ended
		if (mLevelHandler.GetCurrentLevel().FoodExists() == true)
		{
			if (mFruit.IsLifeTimeOver(dt) == true)
			{
				mLevelHandler.GetCurrentLevel().RemoveFood();
			}
		}

		//Test if Pacman collides with ghosts and if any ghosts are ressurected
		for(int g = 0; g < mGhosts.size(); g++)
		{
			if (TestRealCollision(mGhosts[g].GetRealPos(),mPlayer.GetGridPosition()))
			{
				if(mGhosts[g].GetGhostState() == mGhosts[g].Chase || mGhosts[g].GetGhostState() == mGhosts[g].Scatter)
				{
					mGameRestart = true;
					//mGameEventSubscriber->PacmanKilled();
				}
				else if(mGhosts[g].GetGhostState() == mGhosts[g].Frightened)
				{
					mGhosts[g].SetGhostState(mGhosts[g].Killed);
					//mGameEventSubscriber->GhostEaten(g);
					int k = 100;
					for each (Ghost c in mGhosts)
						if (c.GetGhostState() == c.Killed)
							k * 2; //One dead ghost -> 200, 2 -> 400, 3 -> 800, 4 -> 1600
					mScore += k;
				}
			}
			if(mGhosts[g].GetGhostState() == mGhosts[g].Killed)
			{
				if(TestGridCollision(mGhosts[g].GetGridPosition(), mGhosts[g].GetSpawnPosition()))
				{
					mGhosts[g].SetGhostState(mGhosts[g].Chase);
					//mGameEventSubscriber->GhostResurrected(g);
				}
			}
			//Testing message
			char buffer[512];
			sprintf(buffer,"%d",g);
			OutputDebugString("\n--Model Testing--:  Ghost nr:" + g );
			OutputDebugString(buffer);
			OutputDebugString(" Ghost RealPos X:"/* + (int)mGhosts[g].GetRealPos().X */);
			OutputDebugString(" Ghost RealPos Y:"/* + (int)mGhosts[g].GetRealPos().Y */);
			OutputDebugString("\n");
		}

		//Test if level is cleared
		if(mLevelHandler.GetCurrentLevel().GetPelletPositions().size() == 0 && mLevelHandler.GetCurrentLevel().GetPowerPelletPositions().size() == 0)
		{
			//mGameEventSubscriber->GameWon();
			mLevelWasWon = true;
		}

		//Test if time has run out
		if(GetTimeLeft() <= 0)
		{
			mGameRestart = true;
			//mGameEventSubscriber->PacmanKilled();
		}
	}


	bool GameplayHandler::TestGridCollision(Coord objectPos1, Coord objectPos2)
	{
		return (objectPos1 == objectPos2);
	}
	bool GameplayHandler::TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos)
	{ 
		if(sqrt(pow((ghostRealPos.X - pacmanRealPos.X),2) + pow((ghostRealPos.Y - pacmanRealPos.Y),2)) < 0.5)
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

	Level GameplayHandler::GetLevel()
	{
		return mLevelHandler.GetCurrentLevel();
	}

	int GameplayHandler::GetCurrentlevelIndex() const
	{
		return mLevelHandler.GetCurrentLevelIndex();
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
		return (30000 - mGameTime);
	}

	void GameplayHandler::NewLevel()
	{
		//mLevelHandler.SetCurrentLevelIndex(mLevelHandler.GetCurrentLevelIndex() + 1);
		mLevelHandler.NextLevel();
		//mLevel = mLevelHandler.GetCurrentLevel();
		mCurrentLevel = mLevelHandler.GetCurrentLevelIndex() +1;
		mGhosts.clear();
		for (int i = 0; i < 4; i++)
			mGhosts.push_back(Ghost(mLevelHandler.GetCurrentLevel().GetGhostSpawnPositions()[i], i));
		mPlayer = Player(mLevelHandler.GetCurrentLevel().GetPacmanSpawnPosition());
		mLevelWasWon = false;
		mGameRestart = false;
		mPelletsEaten = 0;
		mGameTime = 0;
		mPowerModeTimer = 0;
		//Testing message
		OutputDebugString("--Model Testing--:  NewLevel() function called \n");
	}

	void GameplayHandler::ResetGame()
	{
		//mLevelHandler.SetCurrentLevelIndex(0);
		mLevelHandler.ResetCurrentLevelIndex();
		//mLevel = mLevelHandler.GetCurrentLevel();
		mCurrentLevel = mLevelHandler.GetCurrentLevelIndex() +1;
		mGhosts.clear();
		for (int i = 0; i<=3; i++)
			mGhosts.push_back(Ghost(mLevelHandler.GetCurrentLevel().GetGhostSpawnPositions()[i], i));
		mPlayer = Player(mLevelHandler.GetCurrentLevel().GetPacmanSpawnPosition());
		mScore = 0;
		mLives = 3;
		mGameRestart = false;
		mLevelWasWon = false;
		mPelletsEaten = 0;
		mGameTime = 0;
		mPowerModeTimer = 0;
		//Testing message
		OutputDebugString("--Model Testing--:  ResetGame() function called \n");
	}


}
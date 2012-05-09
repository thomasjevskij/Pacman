#include "GameplayHandler.hpp"

namespace Model
{
	GameplayHandler::GameplayHandler(): mPlayer(Coord(1,1)), mFruit()
	{
		mGameRestart = true;
		srand(NULL);

		//Testing message
		OutputDebugString("--Model Testing--:  Gameplayhandler initiated");
	}

	void GameplayHandler::Update(float dt)
	{
		
		//Testing message
		OutputDebugString("--Model Testing--:  Update() function called");


		//Test if it should to load the next level
		if (mLevelWasWon == true)
			NewLevel();

		//Test if it should start a new game
		if (mGameRestart == true)
			ResetGame();

		
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
				mGameEventSubscriber->PowerPelletEnd();
			}
		}

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
			mPowerModeTimer = dt;
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

		//Test if Pacman collides with ghosts and if any ghosts are ressurected
		for(int g = 0; g < mGhosts.size(); g++)
		{
			if (TestRealCollision(mGhosts[g].GetRealPos(),mPlayer.GetGridPosition()))
			{
				if(mGhosts[g].GetGhostState() == mGhosts[g].Chase || mGhosts[g].GetGhostState() == mGhosts[g].Scatter)
				{
					mGameRestart = true;
					mGameEventSubscriber->PacmanKilled();
				}
				else if(mGhosts[g].GetGhostState() == mGhosts[g].Frightened)
				{
					mGhosts[g].SetGhostState(mGhosts[g].Killed);
					mGameEventSubscriber->GhostEaten(g);
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
					mGameEventSubscriber->GhostResurrected(g);
				}
			}
			//Testing message
			OutputDebugString("--Model Testing--:  (Update)Ghost nr:" + g );
			OutputDebugString("--Model Testing--:  (Update)Ghost GridPos X:" + (int)mGhosts[g].GetGridPosition().X );
			OutputDebugString("--Model Testing--:  (Update)Ghost GridPos Y:" + (int)mGhosts[g].GetGridPosition().Y );
			OutputDebugString("--Model Testing--:  (Update)Ghost RealPos X:" + (int)mGhosts[g].GetRealPos().X );
			OutputDebugString("--Model Testing--:  (Update)Ghost RealPos Y:" + (int)mGhosts[g].GetRealPos().Y );
		}

		//Test if level is cleared
		if(mLevel.GetPelletPositions().size() == 0 && mLevel.GetPowerPelletPositions().size() == 0)
		{
			mGameEventSubscriber->GameWon();
			mLevelWasWon = true;
		}

		//Test if time has run out
		if(GetTimeLeft() <= 0)
		{
			mGameRestart = true;
			mGameEventSubscriber->PacmanKilled();
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
		return (30000 - mGameTime);
	}

	void GameplayHandler::NewLevel()
	{
		mLevelHandler.SetCurrentLevelIndex(mLevelHandler.GetCurrentLevelIndex() + 1);
		mLevel = mLevelHandler.GetCurrentLevel();
		mCurrentLevel = mLevelHandler.GetCurrentLevelIndex() +1;
		mGhosts.clear();
		for (int i = 0; i < 4; i++)
			mGhosts.push_back(Ghost(mLevel.GetGhostSpawnPositions()[i], i));
		mPlayer = Player(mLevel.GetPacmanSpawnPosition());
		mLevelWasWon = false;
		mPelletsEaten = 0;
		mGameTime = 0;
		//Testing message
		OutputDebugString("--Model Testing--:  NewLevel() function called");
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
		mGameTime = 0;
		//Testing message
		OutputDebugString("--Model Testing--:  ResetGame() function called");
	}


}
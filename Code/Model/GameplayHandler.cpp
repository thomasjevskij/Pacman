#include "GameplayHandler.hpp"

namespace Model
{
	GameplayHandler::GameplayHandler(): mPlayer(Coord(1,1))
	{
		mLevel = mLevelHandler.GetCurrentLevel();
	}
	
	void GameplayHandler::Update(float dt)
	{
		//Update movement
		mPlayer.UpdateMovement(dt);
		for each( Ghost g in mGhosts)
			g.UpdateMovement(mPlayer.GetRealPos());

		//Test if Pacman is eating anything
		if (mLevel.GetCell(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y).Type == Cell::C_CELLTYPE_PELLET)
		{
			//add score, notify view
			mLevel.SetEaten(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y);
		}
		else if (mLevel.GetCell(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y).Type == Cell::C_CELLTYPE_POWERPELLET)
		{
			//add score, start powermode, notify view
			mLevel.SetEaten(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y);
		}
		else if (mLevel.GetCell(mPlayer.GetGridPosition().X, mPlayer.GetGridPosition().Y).Type == Cell::C_CELLTYPE_FOOD)
		{
			//calculate and add score, remove fruitobject
			mLevel.RemoveFood();
		}

		//Test if Pacman collides with ghosts
		for each (Ghost g in mGhosts)
		{
			if (TestRealCollision(g.GetRealPos(),mPlayer.GetRealPos()))
			{
				//if(g.GetGhostState() == g.Chase || g.GetGhostState() == g.Scatter)
				//{
				//	//Kill Pacman, end game etc
				//}
				//else if(g.GetGhostState() == g.Frightened)
				//{
				//	// Kill Ghost, add points
				//	//g.SetGhostState(Ghost::GhostState.Killed);
				//}
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
}
#include "GameplayHandler.hpp"

namespace Model
{
	GameplayHandler::GameplayHandler()
	{
		mLevel = mLevelHandler.GetCurrentLevel();
	}

	void GameplayHandler::Update(Framework::GameTime gameTime)
	{
		//Update movement
		player.UpdateMovement();
		for each( Ghost g in ghosts)
			g.UpdateMovement(player.GetRealPos());

		//Test if Pacman is eating anything
		if (mLevel.GetCell(player.GetGridPosition().X, player.GetGridPosition().Y).Type == Cell::C_CELLTYPE_PELLET)
		{
			//add score, notify view
			mLevel.SetEaten(player.GetGridPosition().X, player.GetGridPosition().Y);
		}
		else if (mLevel.GetCell(player.GetGridPosition().X, player.GetGridPosition().Y).Type == Cell::C_CELLTYPE_POWERPELLET)
		{
			//add score, start powermode, notify view
			mLevel.SetEaten(player.GetGridPosition().X, player.GetGridPosition().Y);
		}
		else if (mLevel.GetCell(player.GetGridPosition().X, player.GetGridPosition().Y).Type == Cell::C_CELLTYPE_FOOD)
		{
			//calculate and add score, remove fruitobject
			mLevel.RemoveFood();
		}

		//Test if Pacman collides with ghosts
		for each (Ghost g in ghosts)
		{
			if (TestRealCollision(g.GetRealPos(),player.GetRealPos()))
			{
				if(g.GetGhostState() == Ghost::GhostState.Chase || g.GetGhostState() == Ghost::GhostState.Scatter)
				{
					//Kill Pacman, end game etc
				}
				else if(g.GetGhostState() == Ghost::GhostState.Frightened)
				{
					// Kill Ghost, add points
					//g.SetGhostState(Ghost::GhostState.Killed);
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
	bool GameplayHandler::TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos){}
	


	GameObject GameplayHandler::GetPacman()
	{
		return player;
	}

	std::vector<GameObject> GameplayHandler::GetGhosts()
	{
		return ghosts;
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
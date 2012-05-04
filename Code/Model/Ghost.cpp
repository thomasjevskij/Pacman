#include "Ghost.hpp"
#include "Blinky.hpp"
#include "Pinky.hpp"
#include "Inky.hpp"
#include "Clyde.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition, int aiType)
	{
		mSpawnPosition = gridPosition;
		//Sätt mRealPosition till start värde ändra 64 beroende på hur stora runtorna blir i slut änden
		mRealPosition = Helper::Point2f(gridPosition.X - 0.5 ,gridPosition.Y - 0.5 );
		mFacing = Coord(1,0);
		mMovementSpeed = 2;
		if (aiType == 0)
			mPersonality = new Blinky();
		else if(aiType == 1)
			mPersonality = new Pinky();
		else if(aiType == 2)
			mPersonality = new Inky();
		else
			mPersonality = new Clyde();

	}

	void Ghost::UpdateMovement(Coord playerPosition, float dt, Level* level, Player* player, Coord blinkyPos)
	{
		if(CenterPos())
		{
			//check if current gridpos is an intersection
			//if killed get ghostspawn from level 
			//mPersonality->GetTargetPosition(player, mGhostState, mGridPosition, blinkyPos)
			//Compare possible alternatives to target
			//Change facing (revesed not allowed)

			std::vector<Coord> possibleGrids;
			Coord backFacing = Coord(mGridPosition.X + mFacing.X * -1,mGridPosition.Y + mFacing.Y * -1);
			//Find possible routes
			if(level->GetCell(mGridPosition.X + 1, mGridPosition.Y).Type != Model::Cell::C_CELLTYPE_WALL && 
				Coord(mGridPosition.X + 1, mGridPosition.Y) != backFacing)
			{
				possibleGrids.push_back(Coord(mGridPosition.X + 1, mGridPosition.Y));
			}
			if(level->GetCell(mGridPosition.X - 1, mGridPosition.Y).Type != Model::Cell::C_CELLTYPE_WALL && 
				Coord(mGridPosition.X - 1, mGridPosition.Y) != backFacing)
			{
				possibleGrids.push_back(Coord(mGridPosition.X - 1, mGridPosition.Y));
			}
			if(level->GetCell(mGridPosition.X, mGridPosition.Y + 1).Type != Model::Cell::C_CELLTYPE_WALL && 
				Coord(mGridPosition.X, mGridPosition.Y + 1) != backFacing)
			{
				possibleGrids.push_back(Coord(mGridPosition.X, mGridPosition.Y + 1));
			}
			if(level->GetCell(mGridPosition.X, mGridPosition.Y - 1).Type != Model::Cell::C_CELLTYPE_WALL && 
				Coord(mGridPosition.X, mGridPosition.Y - 1) != backFacing)
			{
				possibleGrids.push_back(Coord(mGridPosition.X, mGridPosition.Y - 1));
			}
			//Choose a route
			if(possibleGrids.size() == 1)
				mFacing == mGridPosition - possibleGrids[0];
			else
			{
				Coord target;
				if(mGhostState == GhostState::Killed)
					target = mSpawnPosition;
				else
					 target = mPersonality->GetTargetPosition(player, mGhostState, mGridPosition, blinkyPos);
				Coord shortestFacing = Coord(1000000,1000000);
				for each (Coord c in possibleGrids)
					if (pow((target.X - c.X),2) + pow((target.Y - c.Y),2) < pow((target.X - shortestFacing.X),2) + pow((target.Y - shortestFacing.Y),2))
						shortestFacing = c;
				mFacing = shortestFacing;
			}

		} 
		mRealPosition += Helper::Point2f(mFacing.X * mMovementSpeed * dt, mFacing.Y * mMovementSpeed * dt);
		mGridPosition = Coord((int)mRealPosition.X,(int)mRealPosition.Y);
	}
	
	Coord Ghost::GetFacing() const
	{
		return mFacing;
	}

	Coord Ghost::GetRealPos() const
	{
		return mRealPosition;
	}

	void Ghost::SetGhostState(GhostState state)
	{
		mGhostState = state;
		if(state == GhostState::Frightened)
		{
			mFacing.X *= -1;
			mFacing.Y *= -1;
			mMovementSpeed = 1.6;
		}
		else if(state == GhostState::Killed)
		{
			mMovementSpeed = 2;
		}
		else if(state == GhostState::Chase)
		{
			mMovementSpeed = 1.8;
		}
		else if(state == GhostState::Scatter)
		{
			mMovementSpeed = 1.8;
		}
	}

	Ghost::GhostState Ghost::GetGhostState()
	{
		return mGhostState;
	}

	Coord Ghost::GetGridPosition() const 
	{
		return mGridPosition;
	}
	
	Coord Ghost::GetSpawnPosition() const 
	{
		return mSpawnPosition;
	}

	void Ghost::GhostStateBehaviour(float gameTime, int levelIndex)
	{
		//Check if the ghost should change state
		if(mGhostState != GhostState::Frightened && mGhostState != GhostState::Killed)
		{
			if (levelIndex == 1)
			{
				if(gameTime <= 7 || gameTime >=27 && gameTime <= 34 || gameTime >=54 && gameTime <= 61  || gameTime >=81 && gameTime <= 88)
					mGhostState = GhostState::Scatter;
				else
					mGhostState = GhostState::Chase;
			}
			else if (levelIndex >= 2 && levelIndex <= 4)
			{
				if(gameTime <= 7 || gameTime >=27 && gameTime <= 34 || gameTime >=54 && gameTime <= 61)
					mGhostState = GhostState::Scatter;
				else
					mGhostState = GhostState::Chase;
			}
			else
			{
				if(gameTime <= 5 || gameTime >=25 && gameTime <= 30 || gameTime >=50 && gameTime <= 55)
					mGhostState = GhostState::Scatter;
				else
					mGhostState = GhostState::Chase;
			}
		}
	}

	bool Ghost::CenterPos()
	{
		//Checks if the ghost is close enough to the center of the tile to turn
		if(mRealPosition.X > mGridPosition.X + 0.4 && mRealPosition.X < mGridPosition.X + 0.6)
		{
			if(mRealPosition.Y > mGridPosition.Y + 0.4 && mRealPosition.Y < mGridPosition.Y + 0.6)
			{
				return true;
			}
		}
		return false;
	}
}
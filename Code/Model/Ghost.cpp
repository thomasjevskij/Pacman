#include "Ghost.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition) : GameObject(gridPosition)
	{
		//Sätt mRealPosition till start värde ändra 64 beroende på hur stora runtorna blir i slut änden
		mRealPosition = Helper::Point2f(gridPosition.X * C_TILESIZE - 32,gridPosition.Y * C_TILESIZE - C_TILESIZE/2);
		mFacing = Coord(1,0);
		mMovementSpeed = 16;
	}

	void Ghost::UpdateMovement(Coord playerPosition, float dt, Level* level, Player* player)
	{
		if(CenterPos())
		{
			//check if current gridpos is an intersection
			//if killed get ghostspawn from level or
			//if frightened choose random route else -DO NOT-
			//mPersonality.GetTargetPosition(player, state)
			//Compare possible alternative grids to target
			//Change facing (revesed not allowed)
		}
		mRealPosition += Helper::Point2f(mFacing.X*mMovementSpeed*dt,mFacing.Y*mMovementSpeed*dt);
		mGridPosition = Coord(mRealPosition.X / C_TILESIZE,mRealPosition.Y / C_TILESIZE);
	}
	
	Coord Ghost::GetFacing()
	{
		return mFacing;
	}

	Coord Ghost::GetRealPos()
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
			mMovementSpeed = 10;
		}
		else if(state == GhostState::Killed)
		{
			mMovementSpeed = 16;
		}
		else if(state == GhostState::Chase)
		{
			mMovementSpeed = 14;
		}
		else if(state == GhostState::Scatter)
		{
			mMovementSpeed = 14;
		}
	}

	Ghost::GhostState Ghost::GetGhostState()
	{
		return mGhostState;
	}

	void Ghost::GhostStateBehaviour(float gameTime, int levelIndex)
	{
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
		if((int)mRealPosition.X % C_TILESIZE > C_TILESIZE/2 - C_TILESIZE/10 && (int)mRealPosition.X % C_TILESIZE < C_TILESIZE/2 + C_TILESIZE/10)
		{
			if((int)mRealPosition.Y % C_TILESIZE > C_TILESIZE/2 - C_TILESIZE/10 && (int)mRealPosition.Y % C_TILESIZE < C_TILESIZE/2 + C_TILESIZE/10)
			{
				return true;
			}
		}
		return false;
	}
}
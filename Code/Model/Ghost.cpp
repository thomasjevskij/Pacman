#include "Ghost.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition, int aiType)
	{
		mSpawnPosition = gridPosition;
		//Sätt mRealPosition till start värde ändra 64 beroende på hur stora runtorna blir i slut änden
		mRealPosition = Helper::Point2f(gridPosition.X * C_TILESIZE - 32,gridPosition.Y * C_TILESIZE - C_TILESIZE/2);
		mFacing = Coord(1,0);
		mMovementSpeed = 16;
		//if (aiType == 0)
		//	mPersonality = new Blinky;
	}

	void Ghost::UpdateMovement(Coord playerPosition, float dt, Level* level, Player* player, Coord blinkyPos)
	{
		if(CenterPos())
		{
			//check if current gridpos is an intersection
			//if killed get ghostspawn from level 
			//mPersonality.GetTargetPosition(player, mGhostState, mGridPosition, blinkyPos)
			//Compare possible alternatives to target
			//Change facing (revesed not allowed)
			std::vector<Coord> possibleGrids;
			Coord backFacing = Coord(mGridPosition.X + mFacing.X * -1,mGridPosition.Y + mFacing.Y * -1);
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
			
			if(possibleGrids.size() == 1)
				mFacing == mGridPosition - possibleGrids[0];
			else
			{
				Coord target;
				if(mGhostState == GhostState::Killed)
					target = mSpawnPosition;
				else
					target = Coord(1,1);
					//Coord target = mPersonality.GetTargetPosition(player, mGhostState, mGridPosition, blinkyPos);
				Coord shortestFacing = Coord(1000000,1000000);
				for each (Coord c in possibleGrids)
					if (pow((target.X - c.X),2) + pow((target.Y - c.Y),2) < pow((target.X - shortestFacing.X),2) + pow((target.Y - shortestFacing.Y),2))
						shortestFacing = c;
				mFacing = shortestFacing;
			}

		} 
		mRealPosition += Helper::Point2f(mFacing.X * mMovementSpeed * dt, mFacing.Y * mMovementSpeed * dt);
		mGridPosition = Coord(mRealPosition.X / C_TILESIZE,mRealPosition.Y / C_TILESIZE);
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

	Coord Ghost::GetGridPosition() const 
	{
		return mGridPosition;
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
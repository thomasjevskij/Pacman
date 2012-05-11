#include "Ghost.hpp"
#include "Blinky.hpp"
#include "Pinky.hpp"
#include "Inky.hpp"
#include "Clyde.hpp"

#include <cassert>
#include "DebuggingParts.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition, int aiType)
	{
		mSpawnPosition = gridPosition;
		//Sätt mRealPosition till start värde ändra 64 beroende på hur stora runtorna blir i slut änden
		mRealPosition = Helper::Point2f(gridPosition.X + 0.5 ,gridPosition.Y + 0.5 );
		mFacing = Coord(0,1);
		mMovementSpeed = 1;
		mHasTurned = false;
		mGhostState = GhostState::Chase;
		if (aiType == 0)
			mPersonality = new Blinky();
		else if(aiType == 1)
			mPersonality = new Pinky();
		else if(aiType == 2)
			mPersonality = new Inky();
		else
			mPersonality = new Clyde();

		OutputDebugString("--Model Testing--:  Ghost Initiated \n");
	}

	void Ghost::UpdateMovement(Coord playerPosition, float dt, Level* level, Player* player, Coord blinkyPos)
	{
		
		OutputDebugString("--Model Testing--:  Ghost::UpdateMovement() function called \n");
		if(CenterPos())
		{
			if(mHasTurned == false)
			{
				OutputDebugString("--Model Testing--:  CenterPos() returned positive \n");

			//check if current gridpos is an intersection
			//if killed get ghostspawn from level 
			//mPersonality->GetTargetPosition(player, mGhostState, mGridPosition, blinkyPos)
			//Compare possible alternatives to target
			//Change facing (revesed not allowed)

			std::vector<Coord> possibleGrids;
			Helper::Point2i backFacing = Helper::Point2i(mGridPosition.X + mFacing.X * -1, mGridPosition.Y + mFacing.Y * -1);
			//Find possible routes
			if(level->GetCell(mGridPosition.X + 1, mGridPosition.Y).Type != Model::Cell::C_CELLTYPE_WALL && 
				Helper::Point2i(mGridPosition.X + 1, mGridPosition.Y) != backFacing)
			{
				possibleGrids.push_back(Coord(mGridPosition.X + 1, mGridPosition.Y));
				OutputDebugString("--Model Testing--:  Path Right is possible \n");
			}
			if(level->GetCell(mGridPosition.X - 1, mGridPosition.Y).Type != Model::Cell::C_CELLTYPE_WALL && 
				Helper::Point2i(mGridPosition.X - 1, mGridPosition.Y) != backFacing)
			{
				possibleGrids.push_back(Coord(mGridPosition.X - 1, mGridPosition.Y));
				OutputDebugString("--Model Testing--:  Path Left is possible \n");
			}
			if(level->GetCell(mGridPosition.X, mGridPosition.Y + 1).Type != Model::Cell::C_CELLTYPE_WALL && 
				Helper::Point2i(mGridPosition.X, mGridPosition.Y + 1) != backFacing)
			{
				possibleGrids.push_back(Coord(mGridPosition.X, mGridPosition.Y + 1));
				OutputDebugString("--Model Testing--:  Path Up is possible \n");
			}
			if(level->GetCell(mGridPosition.X, mGridPosition.Y - 1).Type != Model::Cell::C_CELLTYPE_WALL && 
				Helper::Point2i(mGridPosition.X, mGridPosition.Y - 1) != backFacing)
			{
				possibleGrids.push_back(Coord(mGridPosition.X, mGridPosition.Y - 1));
				OutputDebugString("--Model Testing--:  Path Down is possible \n");
			}
			//Choose a route
			OutputDebugString("--Model Testing--: Choosing route \n");
			assert(possibleGrids.size() > 0);
			if(possibleGrids.size() == 1)
			{
				mFacing =  possibleGrids[0] - mGridPosition;
				OutputDebugString("--Model Testing--:  Ghost has taken the only way possible \n");
			}
			else
			{
				Coord target;
				if(mGhostState == GhostState::Killed)
				{
					
					OutputDebugString("\n--Model Testing--:  Ghost is dead and looking for home \n \n \n");
					target = mSpawnPosition;
				}
				else
					 target = mPersonality->GetTargetPosition(player, mGhostState, mGridPosition, blinkyPos);
				Coord shortestFacing = Coord(1000000,1000000);
				for(int c = 0; c < possibleGrids.size(); c++)
				{
					if (pow((target.X - possibleGrids[c].X),2) + pow((target.Y - possibleGrids[c].Y),2) < pow((target.X - shortestFacing.X),2) + pow((target.Y - shortestFacing.Y),2))
						shortestFacing = possibleGrids[c];
				}
				mFacing = shortestFacing - mGridPosition;
				OutputDebugString("--Model Testing--:  Ghost has choosen a possible way \n");
			}
			}
			mHasTurned = true;
		} 
		else
		{
			mHasTurned = false;
		}
		//mRealPosition += Helper::Point2f(mFacing.X * mMovementSpeed * dt, mFacing.Y * mMovementSpeed * dt);
		mRealPosition.X += mFacing.X * mMovementSpeed * dt;
		mRealPosition.Y += mFacing.Y * mMovementSpeed * dt;
		mRealPosition = GetValidGridPos(mRealPosition,level->GetWidth(), level->GetHeight());
		mGridPosition = Coord((int)mRealPosition.X,(int)mRealPosition.Y);

		//DbgOutFloat(" --Model Testing--: mRealPosition.X = ",mRealPosition.X);
		//DbgOutFloat("\n --Model Testing--: mRealPosition.Y = ",mRealPosition.Y);
		//DbgOutFloat("\n --Model Testing--: mGridPos.X = ",mGridPosition.X);
		//DbgOutFloat("\n --Model Testing--: mGridPos.Y = ", mGridPosition.Y);
		OutputDebugString(" \n");
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
			//mFacing.X *= -1;
			//mFacing.Y *= -1;
			mMovementSpeed = 0.8;
		}
		else if(state == GhostState::Killed)
		{
			mMovementSpeed = 1;
		}
		else if(state == GhostState::Chase)
		{
			mMovementSpeed = 0.9;
		}
		else if(state == GhostState::Scatter)
		{
			mMovementSpeed = 0.9;
		}
	}

	Ghost::GhostState Ghost::GetGhostState() const
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

	Helper::Point2f Ghost::GetValidGridPos(Coord pos,int width,int height)
	{
		if(pos.X < 0)
		{
			pos.X = width-1;
		}
		else if( pos.X > width-1)
		{
			pos.X = 0;
		}

		if(pos.Y < 0)
		{
			pos.Y = height-1;
		}
		else if( pos.Y > height-1)
		{
			pos.Y = 0;
		}
		return pos;
	}

	bool Ghost::CenterPos()
	{
		//Checks if the ghost is close enough to the center of the tile to turn
		if(mRealPosition.X > mGridPosition.X + 0.35 && mRealPosition.X < mGridPosition.X + 0.65)
		{
			if(mRealPosition.Y > mGridPosition.Y + 0.35 && mRealPosition.Y < mGridPosition.Y + 0.65)
			{
				return true;
			}
		}
		return false;
	}
}
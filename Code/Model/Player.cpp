#include "Player.hpp"

namespace Model
{
	Player::Player()
	{}
	Player::Player(Coord gridPosition)
	{
		//Sätt mRealPosition till start värde ändra 64 beroende på hur stora runtorna blir i slut änden
		mRealPosition = Helper::Point2f(gridPosition.X * tileSize - 32,gridPosition.Y * tileSize - tileSize/2);
		mFacing = Coord(1,0);
	}

	void Player::UpdateMovement(Level *level,float dt)
	{
		if(CenterPos())
		{
			Coord validCoord = GetValidGridPos(mGridPosition + mFacing,level->GetWidth(), level->GetHeight());
			Cell forwardCell = level->GetCell(validCoord.X,validCoord.Y);
			if(forwardCell.Type == Cell::C_CELLTYPE_WALL)
			{
				if(mFacing == mLastFacing)
				{
					return;
				}
				else
				{
					mFacing = mLastFacing;
				}
			}
		}

		//Updatera pacmans position
		mRealPosition += Helper::Point2f(mFacing.X*cMovementSpeed*dt,mFacing.Y*cMovementSpeed*dt);
		mGridPosition = Coord(mRealPosition.X / tileSize,mRealPosition.Y / tileSize);
		mLastFacing = mFacing;
		//Glöm ej att uppdatera gridpos
	}

	void Player::GoLeft()
	{	
		if(CenterPos())
		mFacing = Coord(mFacing.Y*-1,mFacing.X);
	}

	void Player::GoRight()
	{
		if(CenterPos())
		mFacing = Coord(mFacing.Y,mFacing.X*-1);
	}

	void Player::GoBack()
	{
		mFacing = Coord(mFacing.X*-1,mFacing.Y*-1);
	}

	Coord Player::GetGridPosition() const 
	{
		return mGridPosition;
	}

	Helper::Point2f Player::GetRealPos() const
	{
		return mRealPosition;
	}

	Coord Player::GetFacing() const
	{
		return mFacing;
	}

	Coord Player::GetValidGridPos(Coord pos,int width,int height)
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
		// DEBUG: added this because the function must return a value!
		return pos;
	}

	bool Player::CenterPos()
	{
		if((int)mRealPosition.X % tileSize > tileSize/2 - tileSize/10 && (int)mRealPosition.X % tileSize < tileSize/2 + tileSize/10)
		{
			if((int)mRealPosition.Y % tileSize > tileSize/2 - tileSize/10 && (int)mRealPosition.Y % tileSize < tileSize/2 + tileSize/10)
			{
				return true;
			}
		}
		return false;
	}
}

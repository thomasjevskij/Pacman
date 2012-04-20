#include "Player.hpp"

namespace Model
{
	Player::Player(Coord gridPosition) : GameObject(gridPosition)
	{
		//Sätt mRealPosition till start värde ändra 64 beroende på hur stora runtorna blir i slut änden
		mRealPosition = Helper::Point2f(gridPosition.X * tileSize - 32,gridPosition.Y * tileSize - tileSize/2);
		mFacing = Coord(1,0);
	}

	void Player::UpdateMovement(Level *level,float dt)
	{
		
			
		Cell forwardCell = level->GetCell(GetValidGridPos(mGridPosition + mFacing,level->GetWhidth(), level->GetHeight()));
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

		//Updatera pacmans position
		mRealPosition += Helper::Point2f(mFacing.X*cMovementSpeed*dt,mFacing.Y*cMovementSpeed*dt);
		mGridPosition = Coord(mRealPosition.X / tileSize,mRealPosition.Y / tileSize);
		mLastFacing = mFacing;
		//Glöm ej att uppdatera gridpos
	}

	void Player::GoLeft()
	{	
		if()
		mFacing = Coord(mFacing.Y*-1,mFacing.X);
	}

	void Player::GoRight()
	{

		mFacing = Coord(mFacing.Y,mFacing.X*-1);
	}

	void Player::GoBack()
	{
		mFacing = Coord(mFacing.X*-1,mFacing.Y*-1);
	}


	Helper::Point2f Player::GetRealPos() const
	{
		return mRealPosition;
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

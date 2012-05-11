#include "Player.hpp"

namespace Model
{
	Player::Player()
	{}
	Player::Player(Coord gridPosition)
	{
		mRealPosition = Helper::Point2f(gridPosition.X + 0.5 ,gridPosition.Y + 0.5 );
		mFacing = Coord(1,0);
		mMovementSpeed = 1;
		mHasTurned = false;
		OutputDebugString("--Model Testing--:  Player Initiated \n");
	}

	void Player::UpdateMovement(Level *level,float dt)
	{
		Coord validCoord = GetValidGridPos(mGridPosition + mFacing,level->GetWidth(), level->GetHeight());
		OutputDebugString("--Model Testing--:  Player::UpdateMovement() function called \n");
		if(CenterPos())
		{
	
			OutputDebugString("--Model Testing--:  CenterPos() returned positive \n");
			Cell testCell = level->GetCell(mGridPosition.X,mGridPosition.Y);
			Cell forwardCell = level->GetCell(validCoord.X,validCoord.Y);
			if(forwardCell.Type == Cell::C_CELLTYPE_WALL)
			{
				if(mFacing == mLastFacing)
				{
					OutputDebugString("--Model Testing--: Packade packis gick i en wall \n");
					return;
				}
				else
				{
					mFacing = mLastFacing;
				}
			}
			mHasTurned = true;
		}
		else
		{
			mHasTurned = false;
		}
		validCoord = GetValidGridPos(mGridPosition + mFacing,level->GetWidth(), level->GetHeight());
		//Updatera pacmans position

		if(level->GetCell(validCoord.X,validCoord.Y).Type == Cell::C_CELLTYPE_WALL && CenterPos())
		{}
		else
		{
			mRealPosition.X += mFacing.X * mMovementSpeed * dt;
			mRealPosition.Y += mFacing.Y * mMovementSpeed * dt;
			mRealPosition = GetValidGridPos(mRealPosition,level->GetWidth(), level->GetHeight());
		}
		mGridPosition = Coord((int)mRealPosition.X,(int)mRealPosition.Y);
		mLastFacing = mFacing;
		
		//DbgOutFloat(" --Model Testing--: mRealPosition.X = ",mRealPosition.X);
		//DbgOutFloat("\n --Model Testing--: mRealPosition.Y = ",mRealPosition.Y);
		//OutputDebugString("\n");
	}

	void Player::GoLeft()
	{	
		if(CenterPos() && mHasTurned == false)
			mFacing = Coord(mFacing.Y*-1,mFacing.X);
	}

	void Player::GoRight()
	{
		if(CenterPos() && mHasTurned == false)
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
		if(mRealPosition.X > mGridPosition.X + 0.4 && mRealPosition.X < mGridPosition.X + 0.6)
		{
			if(mRealPosition.Y > mGridPosition.Y + 0.4 && mRealPosition.Y < mGridPosition.Y + 0.6)
			{
				return true;
			}
		}
		return false;
	}

	const Coord& Player::GetFacing() const
	{
		return mFacing;
	}
}

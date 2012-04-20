#include "Player.hpp"

namespace Model
{
	Player::Player(Coord gridPosition) : GameObject(gridPosition)
	{
		
		//Sätt mRealPosition till start värde
	}

	void Player::UpdateMovement()
	{
		//Updatera pacmans position
		//Glöm ej att uppdatera gridpos
	}

	void Player::GoLeft()
	{
		mFacing = Coord(-1,0);
	}

	void Player::GoRight()
	{
		mFacing = Coord(1,0);
	}

	void Player::GoUp()
	{
		mFacing = Coord(0,1);
	}

	void Player::GoDown()
	{
		mFacing = Coord(0,-1);
	}
}

#ifdef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"

namespace Model
{
	class Player:GameObject
	{
	public:
		Player(Coord gridPosition):GameObject(gridPosition);
		void UpdateMovement();
		void GoLeft();
		void GoRight();
		void GoUp();
		void GoDown();
	private:
		//Facing mFacing
		Coord mRealPosition;
	}
}
#endif
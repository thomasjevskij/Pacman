#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Coord.hpp"

namespace Model
{
	class Player: public GameObject
	{
	public:
		Player(Coord gridPosition); // : GameObject(gridPosition);
		void UpdateMovement();
		void GoLeft();
		void GoRight();
		void GoUp();
		void GoDown();
		Coord GetRealPos(){return mRealPosition;};
	private:
		Coord mFacing; //Enhetsvektor 0,1 = upp, 1,0 = right 0,-1 = down, -1,0 = left
		Coord mRealPosition;
	};
}
#endif
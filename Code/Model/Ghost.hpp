#ifndef GHOST_HPP
#define GHOST_HPP

#include "GameObject.hpp"
#include "Ai.hpp"

namespace Model
{
	class Ghost:public GameObject
	{
	public:
		Ghost(Coord gridPosition,Ai personality):GameObject(gridPosition);
		void UpdateMovement(Coord playerPosition);
		//Facing getFacing(){return mFacing};
	private:
		Ai Personality;
		//Facing mFacing
		Coord mRealPosition;
	};
}
#endif
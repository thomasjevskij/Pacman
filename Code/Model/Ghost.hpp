#ifndef GHOST_HPP
#define GHOST_HPP

#include "Coord.hpp"
#include "GameObject.hpp"
#include "Ai.hpp"

namespace Model
{
	class Ghost : public GameObject
	{
	public:
		Ghost(Coord gridPosition);// : GameObject(gridPosition);
		void UpdateMovement(Coord playerPosition);
		Coord GetFacing(){return mFacing;}
		Coord GetRealPos(){return mRealPosition;}

		enum GhostState{ Scatter, Chase, Frightened, Killed};
		void SetGhostState(GhostState state);
		GhostState GetGhostState();
		
	private:
		GhostState mGhostState;
		//Ai* Personality;
		Coord mFacing; //Enhetsvektor 0,1 = upp, 1,0 = right 0,-1 = down, -1,0 = left
		Coord mRealPosition;
		
		static const int C_TILESIZE = 64;
	};
}
#endif
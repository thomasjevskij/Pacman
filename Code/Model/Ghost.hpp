#ifndef GHOST_HPP
#define GHOST_HPP

#include "Coord.hpp"
#include "GameObject.hpp"
#include "Ai.hpp"
#include "Level.hpp"

namespace Model
{
	class Ghost : public GameObject
	{
	public:
		Ghost(Coord gridPosition);
		void UpdateMovement(Coord playerPosition, float dt, Level* level);
		void GhostStateBehaviour(float gameTime, int levelIndex);

		Coord GetFacing();
		Coord GetRealPos();

		enum GhostState{ Scatter, Chase, Frightened, Killed};
		void SetGhostState(GhostState state);
		GhostState GetGhostState();
		
	private:
		GhostState mGhostState;
		//Ai* mPersonality;
		Coord mFacing; //Enhetsvektor 0,1 = upp, 1,0 = right 0,-1 = down, -1,0 = left
		Coord mRealPosition;
		int mMovementSpeed;

		bool CenterPos();

		static const int C_TILESIZE = 64;
	};
}
#endif
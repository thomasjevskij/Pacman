#ifndef GHOST_HPP
#define GHOST_HPP

#include "Coord.hpp"
#include "Ai.hpp"
#include "Level.hpp"
#include "Player.hpp"
#include "Blinky.hpp"


namespace Model
{
	class Ai;

	class Ghost
	{
	public:
		Ghost(Coord gridPosition, int aiType);
		void UpdateMovement(Coord playerPosition, float dt, Level* level, Player* player, Coord blinkyPos);
		void GhostStateBehaviour(float gameTime, int levelIndex);
		
		Coord GetGridPosition() const;
		Coord GetFacing();
		Coord GetRealPos();

		enum GhostState{ Scatter, Chase, Frightened, Killed};
		void SetGhostState(Ghost::GhostState state);
		GhostState GetGhostState();
		
	private:
		GhostState mGhostState;
		Ai* mPersonality;
		Coord mFacing; //Enhetsvektor 0,1 = upp, 1,0 = right 0,-1 = down, -1,0 = left
		Coord mRealPosition;
		Coord mGridPosition;
		Coord mSpawnPosition;
		int mMovementSpeed;

		bool CenterPos();

		static const int C_TILESIZE = 64;
	};

	class Ai
	{
	public:
		Ai();
		virtual Coord GetTargetPosition(Player* player, Ghost::GhostState state, Coord ghostPos, Coord blinkyPos) = 0;
	protected:
		Coord mScatterSquare;
	};
}
#endif
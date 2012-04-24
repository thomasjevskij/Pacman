#include "Blinky.hpp"

namespace Model
{
	Blinky::Blinky()
	{
		mScatterSquare = Coord(10000, -10000);
	}

	Coord Blinky::GetTargetPosition(Player* player, Ghost::GhostState state)
	{
		//This function does not handle Ghost::Killed since it is much simpler to handle from the Ghost class
		if(state == Ghost::Scatter)
			return mScatterSquare;
		else if(state == Ghost::Frightened)
			return Coord(rand() - RAND_MAX/2, rand() - RAND_MAX);
		else //state == Ghost::Chase
			return player->GetGridPosition();
	}
}
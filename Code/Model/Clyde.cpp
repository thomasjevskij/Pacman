#include "Clyde.hpp"

namespace Model
{
	Clyde::Clyde()
	{
		mScatterSquare = Coord(-10000, 10000);
	}

	Coord Clyde::GetTargetPosition(Player* player, Ghost::GhostState state)
	{
		if(state == Ghost::Scatter)
			return mScatterSquare;
		else if(state == Ghost::Frightened)
			return Coord(rand() - RAND_MAX/2, rand() - RAND_MAX);
		else //state == Ghost::Chase
			return player->GetGridPosition();
	}
}
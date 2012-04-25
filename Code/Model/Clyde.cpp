#include "Clyde.hpp"

namespace Model
{
	Clyde::Clyde()
	{
		mScatterSquare = Coord(-10000, 10000);
	}

	Coord Clyde::GetTargetPosition(Player* player, Ghost::GhostState state, Coord ghostPos, Coord blinkyPos)
	{
		//This function does not handle Ghost::Killed since it is much simpler to handle from the Ghost class
		if(state == Ghost::Scatter)
			return mScatterSquare;
		else if(state == Ghost::Frightened)
			return Coord(rand() - RAND_MAX/2, rand() - RAND_MAX);
		else //state == Ghost::Chase
		{
			if(sqrt(pow((ghostPos.X - player->GetGridPosition().X),2) + pow((ghostPos.Y - player->GetGridPosition().Y),2)) > 8)
				return player->GetGridPosition();
			else
				return mScatterSquare;
		}

	}
}
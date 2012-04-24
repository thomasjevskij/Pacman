#include "Pinky.hpp"

namespace Model
{
	Pinky::Pinky()
	{
		mScatterSquare = Coord(-10000, -10000);
	}

	Coord Pinky::GetTargetPosition(Player* player, Ghost::GhostState state)
	{
		//This function does not handle Ghost::Killed since it is much simpler to handle from the Ghost class
		if(state == Ghost::Scatter)
			return mScatterSquare;
		else if(state == Ghost::Frightened)
			return Coord(rand() - RAND_MAX/2, rand() - RAND_MAX);
		else //state == Ghost::Chase
		{
			Coord target = player->GetGridPosition();
			target.X += player->GetFacing().X * 4;
			target.Y += player->GetFacing().Y * 4; 
			return target;
		}
	}
}
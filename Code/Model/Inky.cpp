#include "Inky.hpp"

namespace Model
{
	Inky::Inky()
	{
		mScatterSquare = Coord(10000, 10000);
	}

	Coord Inky::GetTargetPosition(Player* player, Ghost::GhostState state, Coord ghostPos, Coord blinkyPos)
	{
		//This function does not handle Ghost::Killed since it is much simpler to handle from the Ghost class
		if(state == Ghost::Scatter)
			return mScatterSquare;
		else if(state == Ghost::Frightened)
			return Coord(rand() - RAND_MAX/2, rand() - RAND_MAX);
		else //state == Ghost::Chase
		{
			Coord target;
			Coord vector = player->GetGridPosition();
			vector.X += player->GetFacing().X * 2 - blinkyPos.X;
			vector.Y += player->GetFacing().Y * 2 - blinkyPos.Y; 
			target = blinkyPos + vector + vector;
			return target;
		}
	}
}
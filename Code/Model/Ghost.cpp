#include "Ghost.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition) : GameObject(gridPosition)
	{
		////S�tt mRealPosition till start v�rde �ndra 64 beroende p� hur stora runtorna blir i slut �nden
		//mRealPosition = Helper::Point2f(gridPosition.X * tileSize - 32,gridPosition.Y * tileSize - tileSize/2);
		//mFacing = Coord(1,0);
	}

	void Ghost::UpdateMovement(Coord playerPosition)
	{

		//Gl�m ej att uppdatera gridpos
	}

	void Ghost::SetGhostState(GhostState state)
	{
		mGhostState = state;
	}

	Ghost::GhostState  Ghost::GetGhostState()
	{
		return mGhostState;
	}
}
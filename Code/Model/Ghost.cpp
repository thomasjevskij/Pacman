#include "Ghost.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition) : GameObject(gridPosition)
	{
		////Sätt mRealPosition till start värde ändra 64 beroende på hur stora runtorna blir i slut änden
		//mRealPosition = Helper::Point2f(gridPosition.X * tileSize - 32,gridPosition.Y * tileSize - tileSize/2);
		//mFacing = Coord(1,0);
	}

	void Ghost::UpdateMovement(Coord playerPosition)
	{

		//Glöm ej att uppdatera gridpos
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
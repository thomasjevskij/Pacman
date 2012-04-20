#include "Ghost.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition) : GameObject(gridPosition)
	{
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
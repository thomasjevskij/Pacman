#include "Ghost.hpp"

namespace Model
{
	Ghost::Ghost(Coord gridPosition,Ai personality)
	{
		//Ska nog �ndras s� att man inte skickar in en 
		//hel personlighet utan bara n�got som talar om
		//vilken som ska anv�ndas
		this.Personality = personality;
	}

	Ghost::UpdateMovement(Coord playerPosition)
	{

	}
}
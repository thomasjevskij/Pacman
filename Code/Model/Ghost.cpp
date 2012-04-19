#include "Ghost.hpp"

namespace Model
{
	Ghost::Ghost(Coord gridPosition,Ai personality)
	{
		//Ska nog ändras så att man inte skickar in en 
		//hel personlighet utan bara något som talar om
		//vilken som ska användas
		this.Personality = personality;
	}

	Ghost::UpdateMovement(Coord playerPosition)
	{

	}
}
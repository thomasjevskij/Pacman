#include "Ghost.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition) : GameObject(gridPosition)
	{
		//Ska nog �ndras s� att man inte skickar in en 
		//hel personlighet utan bara n�got som talar om
		//vilken som ska anv�ndas
	}

	void Ghost::UpdateMovement(Coord playerPosition)
	{
		
		//Gl�m ej att uppdatera gridpos
	}

	
	
}
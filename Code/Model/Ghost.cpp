#include "Ghost.hpp"

namespace Model
{

	Ghost::Ghost(Coord gridPosition) : GameObject(gridPosition)
	{
		//Ska nog ändras så att man inte skickar in en 
		//hel personlighet utan bara något som talar om
		//vilken som ska användas
	}

	void Ghost::UpdateMovement(Coord playerPosition)
	{
		
		//Glöm ej att uppdatera gridpos
	}

	
	
}
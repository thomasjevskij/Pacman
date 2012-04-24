#ifndef BLINKY_HPP
#define BLINKY_HPP

#include "Ghost.hpp"
#include "Coord.hpp"

namespace Model
{
	class Blinky : public Ai
	{
	public: 
		Blinky();
		Coord GetTargetPosition(Player* player, Ghost::GhostState state);
	protected:
		Coord ScatterSquare;

	};
}


#endif
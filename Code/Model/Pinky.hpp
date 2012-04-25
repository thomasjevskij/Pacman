#ifndef PINKY_HPP
#define PINKY_HPP

#include "Ghost.hpp"
#include "Coord.hpp"

namespace Model
{
	class Pinky : public Ai
	{
	public: 
		Pinky();
		Coord GetTargetPosition(Player* player, Ghost::GhostState state, Coord ghostPos, Coord blinkyPos);
	protected:
		Coord ScatterSquare;

	};
}


#endif
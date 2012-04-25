#ifndef CLYDE_HPP
#define CLYDE_HPP

#include "Ghost.hpp"
#include "Coord.hpp"

namespace Model
{
	class Clyde : public Ai
	{
	public: 
		Clyde();
		Coord GetTargetPosition(Player* player, Ghost::GhostState state, Coord ghostPos, Coord blinkyPos);
	protected:
		Coord ScatterSquare;

	};
}


#endif
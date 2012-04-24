#ifndef INKY_HPP
#define INKY_HPP

#include "Ghost.hpp"
#include "Coord.hpp"

namespace Model
{
	class Inky : public Ai
	{
	public: 
		Inky();
		Coord GetTargetPosition(Player* player, Ghost::GhostState state);
	protected:
		Coord ScatterSquare;

	};
}


#endif
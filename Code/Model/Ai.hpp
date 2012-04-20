#ifndef AI_HPP
#define AI_HPP

#include "Coord.hpp"

namespace Model
{
	class Ai
	{
	public:
		Ai();
		Ai(Coord homeSquare){HomeSquare = homeSquare;};
		virtual Coord getTargetPosition() = 0;
	protected:
		Coord HomeSquare;
	};
}
#endif
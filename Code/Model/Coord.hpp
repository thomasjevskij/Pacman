#ifndef COORD_HPP
#define COORD_HPP

#include "Primitives.hpp"

namespace Model
{
	typedef Helper::Point2f Coord;  // DEBUG: changed from Point2i to Point2f because of type clash 
									// in method call: UpdateMovement in GameplayHandler.
	//struct Coord
	//{
	//	Coord();
	//	Coord(int x, int y);
	//	bool operator==(const Coord& rhs) const;
	//	int X, Y;
	//};
}
#endif
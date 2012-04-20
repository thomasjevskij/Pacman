#ifndef COORD_HPP
#define COORD_HPP

namespace Model
{
	struct Coord
	{
		Coord();
		Coord(int x, int y);
		bool operator==(const Coord& rhs) const;
		int X, Y;
	};
}
#endif
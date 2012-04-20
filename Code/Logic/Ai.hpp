#ifndef AI_HPP
#define AI_HPP

namespace Model
{
	class Ai
	{
	public:
		Ai(Coord homeSquare){HomeSquare = homeSquare};
		virtual  Coord getTargetPosition(){};
	protected:
		Coord HomeSquare;
	};
}
#endif
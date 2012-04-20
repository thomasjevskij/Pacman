#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Coord.hpp"

namespace Model
{
	class GameObject
	{
	public:
		GameObject(Coord gridPosition) : mGridPosition(gridPosition) {}
		Coord GetGridPosition() const {return GridPosition}

	protected:
		Coord mGridPosition;
	};
}
#endif
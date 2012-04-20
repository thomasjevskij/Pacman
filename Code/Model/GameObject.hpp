#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "Coord.hpp"

namespace Model
{
	class GameObject
	{
	public:
		GameObject(Coord gridPosition) : mGridPosition(gridPosition) {}
		Coord GetGridPosition() const {return mGridPosition;}

	protected:
		Coord mGridPosition;
	};
}
#endif
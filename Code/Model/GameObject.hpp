#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

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
#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

namespace Model
{
	class GameObject
	{
	public:
		GameObject(Coord gridPosition){mGridPosition = gridPosition};
		Coord GetGridPosition(){return GridPosition};
	protected:
		Coord mGridPosition;
	};
}
#endif
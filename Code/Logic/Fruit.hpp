#ifndef FRUIT_HPP
#define FRUIT_HPP

#include "GameObject.hpp"

namespace Model
{
	class Fruit:public GameObject
	{
	public:
		Fruit(Coord gridPosition):GameObjekt(gridPosition);
		bool IsLifeTimeOver();
	private:
		Timer mLifeTimer;
		static const cLifeTime = 10;
	}
}
#endif
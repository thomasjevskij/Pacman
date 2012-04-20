#include "Fruit.hpp"

namespace Model
{
	Fruit::Fruit(Coord gridPosition): GameObject(gridPosition)
	{
		mLivedTime = 0;
	}
	bool Fruit::IsLifeTimeOver(float dt)
	{
		mLivedTime += dt;
		if(mLivedTime >= cEndTime)
		{
			return true;
		}
		return false;
	}
}
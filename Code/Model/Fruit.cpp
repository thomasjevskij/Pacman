#include "Fruit.hpp"

namespace Model
{
	Fruit::Fruit(Coord gridPosition, Helper::GameTime gameTime): GameObject(gridPosition)
	{
		mStartTime = 0;
	}
	bool Fruit::IsLifeTimeOver(Helper::GameTime gameTime)
	{
		mStartTime += gameTime.GetTimeSinceLastTick();
		if(mStartTime >= cLifeTime)
		{
			return true;
		}
		return false;
	}
}
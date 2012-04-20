#include "Fruit.hpp"

namespace Model
{
	Fruit::Fruit(Coord gridPosition, Helper::GameTime gameTime): GameObject(gridPosition)
	{

	}
	bool Fruit::IsLifeTimeOver()
	{
		/*if(mLifeTimer.getElapsedSeconds() >= cLifeTime)
		{
			return true;
		}*/
		return false;
	}
}
#include "Fruit.hpp"

namespace Model
{
	Fruit::Fruit(Coord gridPosition, Framework::GameTime gameTime): GameObject(gridPosition)
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
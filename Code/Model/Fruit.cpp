#include "Fruit.hpp"

namespace Model
{
	bool Fruit::IsLifeTimeOver()
	{
		if(mLifeTimer.getElapsedSeconds() >= cLifeTime)
		{
			return true;
		}
		return false;
	}
}
#include "Fruit.hpp"

namespace Model
{
	Fruit::Fruit()
	{
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
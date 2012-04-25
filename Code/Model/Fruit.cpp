#include "Fruit.hpp"

namespace Model
{
	Fruit::Fruit()
	{
	}
	bool Fruit::IsLifeTimeOver(float dt)
	{
		mLivedTime += dt;
		if(mLivedTime >= C_ENDTIME)
		{
			return true;
		}
		return false;
	}
}
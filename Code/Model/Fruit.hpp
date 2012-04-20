#ifndef FRUIT_HPP
#define FRUIT_HPP

#include "GameObject.hpp"
#include "GameTime.hpp"

namespace Model
{
	class Fruit:public GameObject
	{
	public:
		Fruit(Coord gridPosition);
		bool IsLifeTimeOver(float dt);
	private:
		float mLivedTime;
		static const int cEndTime = 10;
	};
}
#endif
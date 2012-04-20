#ifndef FRUIT_HPP
#define FRUIT_HPP

#include "GameObject.hpp"
#include "GameTime.hpp"

namespace Model
{
	class Fruit:public GameObject
	{
	public:
		Fruit(Coord gridPosition, Helper::GameTime gameTime);
		bool IsLifeTimeOver(Helper::GameTime gameTime);
	private:
		Helper::GameTime mStartTime;
		static const int cLifeTime = 10;
	};
}
#endif
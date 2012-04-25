#ifndef FRUIT_HPP
#define FRUIT_HPP

#include "GameTime.hpp"

namespace Model
{
	class Fruit
	{
	public:
		Fruit();
		bool IsLifeTimeOver(float dt);
	private:
		float mLivedTime;
		static const int C_ENDTIME = 10;
	};
}
#endif
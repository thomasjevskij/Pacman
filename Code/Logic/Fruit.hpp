#ifndef FRUIT_HPP
#define FRUIT_HPP

namespace Model
{
	class Fruit
	{
	public:
		Fruit(){};
		bool IsLifeTimeOver()
	private:
		Timer mLifeTimer;
		static const cLifeTime = 10;
	}
}
#endif
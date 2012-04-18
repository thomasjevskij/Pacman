#ifdef PLAYER_HPP
#define PLAYER_HPP

namespace Model
{
	class Player
	{
	public:
		Player(){}
		void UpdateMovement(){}
		void GoLeft(){}
		void GoRight(){}
		void GoUp(){}
		void GoDown(){}
	private:
		//Facing mFacing
		Coord mRealPosition;
	}
}
#endif
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Coord.hpp"
#include "Level.hpp"


namespace Model
{
	class Player
	{
	public:
		Player();
		Player(Coord gridPosition);
		void UpdateMovement(Level *level,float dt);
		void GoLeft();
		void GoRight();
		void GoBack();

		
		Coord GetGridPosition() const;
		Helper::Point2f GetRealPos() const;
		const Coord& GetFacing() const;

	private:
		Coord mFacing; //Enhetsvektor 0,1 = upp, 1,0 = right 0,-1 = down, -1,0 = left
		Coord mLastFacing;
		Coord mGridPosition;

		Helper::Point2f mRealPosition;
		float mMovementSpeed;

		Coord GetValidGridPos(Coord pos,int width,int height);
		bool CenterPos();
	};
}
#endif
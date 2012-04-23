#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Coord.hpp"
#include "Level.hpp"


namespace Model
{
	class Player: public GameObject
	{
	public:
		Player();
		Player(Coord gridPosition); // : GameObject(gridPosition);
		void UpdateMovement(Level *level,float dt);
		void GoLeft();
		void GoRight();
		void GoBack();
		Helper::Point2f GetRealPos() const;

	private:
		Coord mFacing; //Enhetsvektor 0,1 = upp, 1,0 = right 0,-1 = down, -1,0 = left
		Coord mLastFacing;
		Helper::Point2f mRealPosition;
		static const int cMovementSpeed = 16;
		static const int tileSize = 64;

		Coord GetValidGridPos(Coord pos,int width,int height);
		bool CenterPos();
	};
}
#endif
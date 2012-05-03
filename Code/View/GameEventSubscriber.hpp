#ifndef GAMEEVENTSUBSCRIBER_HPP
#define GAMEEVENTSUBSCRIBER_HPP

#include "Primitives.hpp"

namespace View
{
	class GameEventSubscriber
	{
	public:
		virtual void PelletEaten(Helper::Point2f position)=0;
		virtual void PowerPelletEaten(Helper::Point2f position)=0;
		virtual void PowerPelletEnd()=0;
		virtual void GhostEaten(int index)=0;
		virtual void GhostResurrected(int index)=0;
		virtual void PacmanKilled()=0;
		virtual void GameWon()=0;
	};
}
#endif
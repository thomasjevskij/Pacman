#ifndef GAMEEVENTSUBSCRIBER_HPP
#define GAMEEVENTSUBSCRIBER_HPP

#include "Primitives.hpp"

namespace View
{
	virtual void PelletEaten(Point2i position)=0;
	virtual void PowerPelletEaten(Point2i position)=0;
	virtual void PowerPelletEnd();
	virtual void GhostEaten(int index)=0;
	virtual void GhostResurrected(int index)=0;
	virtual void PacmanKilled()=0;
	virtual void GameWon()=0;
}
#endif
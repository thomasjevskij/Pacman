#ifndef MODELDATAINTERFACE_HPP
#define MODELDATAINTERFACE_HPP

#include "Primitives.hpp"
#include "Level.hpp"
#include <vector>

namespace Model
{
	class ModelDataInterface
	{
	public:
		virtual Helper::Point2f GetPacmanPosition() const = 0;
		virtual Helper::Point2f GetPacmanFacing() const = 0;
		virtual std::vector<Helper::Point2f> GetGhostPositions() const = 0;
		virtual const Level& GetLevel() = 0;
		virtual int GetCurrentLevelIndex() const = 0;
		virtual int GetLives() const = 0;
		virtual int GetScore() const = 0;
		virtual float GetTimeLeft() const = 0;
	};
}

#endif
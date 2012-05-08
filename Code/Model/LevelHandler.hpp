#ifndef LEVELHANDLER_HPP
#define LEVELHANDLER_HPP

#include "Level.hpp"
#include <vector>
#include <string>

namespace Model
{
	class LevelHandler
	{
		//To do: Inladdning av banorna
	public:
		LevelHandler();

		const Level& GetCurrentLevel() const;
		int GetCurrentLevelIndex() const;

		void SetCurrentLevelIndex(int levelIndex);
	private:
		std::vector<Level*> mLevels;
		int mCurrentLevelIndex;
	};
}
#endif
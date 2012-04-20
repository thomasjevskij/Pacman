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
		Level GetCurrentLevel();
		int GetCurrentLevelIndex();
		void SetCurrentLevelIndex(int levelIndex);
	private:
		std::vector<Level> mLevels;
		int mCurrentLevelIndex;
	};
}
#endif
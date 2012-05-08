#include "LevelHandler.hpp"

namespace Model
{
	LevelHandler::LevelHandler()
	{
		mCurrentLevelIndex = 0;
		//Loads Levels into vector

		for(int i = 0; i <= 1; ++i)
			mLevels.push_back(Level("Level"));
	}

	Level LevelHandler::GetCurrentLevel()
	{
		return mLevels[mCurrentLevelIndex % mLevels.size()];
	}
	
	int LevelHandler::GetCurrentLevelIndex()
	{
		return mCurrentLevelIndex;
	}

	void LevelHandler::SetCurrentLevelIndex(int levelIndex)
	{
		mCurrentLevelIndex = levelIndex;
	}


}

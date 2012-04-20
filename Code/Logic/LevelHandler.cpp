#include "LevelHandler.hpp"

namespace Model
{
	
	LevelHandler::LevelHandler()
	{
		//Loads Levels into vector
		std::string temp;
		for(int i = 0; i <= 16; ++i)
			//mLevels.add(new Level("Level" + i + ".png"));
	}

	Level LevelHandler::GetCurrentLevel()
	{
		return mLevels[mCurrentLevelIndex];
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

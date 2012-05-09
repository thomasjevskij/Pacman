#include "LevelHandler.hpp"
#include "FileResourceManager.hpp"

namespace Model
{
	LevelHandler::LevelHandler()
	{
		mCurrentLevelIndex = 0;
		//Loads Levels into vector

		for(int i = 0; i < 1; ++i)
			mLevels.push_back(Resources::FileResourceManager<Level>::Instance().Load("Level.png"));
	}

	const Level& LevelHandler::GetCurrentLevel() const
	{
		return *mLevels[mCurrentLevelIndex % mLevels.size()];
	}
	
	int LevelHandler::GetCurrentLevelIndex() const
	{
		return mCurrentLevelIndex;
	}

	void LevelHandler::SetCurrentLevelIndex(int levelIndex)
	{
		mCurrentLevelIndex = levelIndex;
	}


}

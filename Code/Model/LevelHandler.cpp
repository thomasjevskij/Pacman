#include "LevelHandler.hpp"
#include "FileResourceManager.hpp"

namespace Model
{
	LevelHandler::LevelHandler()
	{
		mCurrentLevelIndex = 0;

		for(int i = 0; i < 1; ++i)
			mLevels.push_back(Resources::FileResourceManager<Level>::Instance().Load("Level.png"));

		mCurrentLevel = *mLevels[0];
		//debug
		OutputDebugString("--Model Testing--:  LevelHandler Initiated \n");
	}

	Level& LevelHandler::GetCurrentLevel()
	{
		return mCurrentLevel;
	}
	
	int LevelHandler::GetCurrentLevelIndex() const
	{
		return mCurrentLevelIndex;
	}

	void LevelHandler::ResetCurrentLevelIndex()
	{
		mCurrentLevelIndex = 0;
	}
	void LevelHandler::NextLevel()
	{
		mCurrentLevelIndex += 1;
		mCurrentLevel = *mLevels[mCurrentLevelIndex % mLevels.size()];
	}

	//void LevelHandler::SetCurrentLevelIndex(int levelIndex)
	//{
	//	mCurrentLevelIndex = levelIndex;
	//}
}

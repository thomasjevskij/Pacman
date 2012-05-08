#include "GameScreen.hpp"
#include "Global.hpp"

namespace View
{
	GameScreen::~GameScreen() throw() {}



	GameScreenHandler::GameScreenHandler()
		: mCurrentScreen(NULL)
		, mNextScreen(NULL)
	{}

	GameScreenHandler::GameScreenHandler(GameScreen* startScreen)
		: mCurrentScreen(startScreen)
		, mNextScreen(startScreen)
	{}

	GameScreenHandler::~GameScreenHandler() throw()
	{
		if (mCurrentScreen == mNextScreen)
		{
			SafeDelete(mCurrentScreen);
		}
		else
		{
			SafeDelete(mCurrentScreen);
			SafeDelete(mNextScreen);
		}
	}


	void GameScreenHandler::ChangeScreen(GameScreen* newScreen)
	{
		mNextScreen = newScreen;
	}

	void GameScreenHandler::UpdateScreen(float dt)
	{
		if (mCurrentScreen != NULL)
			mCurrentScreen->Update(dt);
	}

	void GameScreenHandler::DrawScreen(float dt)
	{
		if (mCurrentScreen != NULL)
			mCurrentScreen->Draw(dt);
	}


	void GameScreenHandler::SwapScreens()
	{
		if (mNextScreen != mCurrentScreen)
		{
			SafeDelete(mCurrentScreen);
			mCurrentScreen = mNextScreen;
		}
	}

}
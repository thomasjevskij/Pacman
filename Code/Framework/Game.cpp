#include "Game.hpp"

namespace Framework
{
	Game::Game(HINSTANCE instance, const ApplicationWindow::Description& windowDescription, const D3DContext::Description& contextDescription)
		: mWindow(instance, windowDescription)
		, mD3DContext(&mWindow, contextDescription)
		, mRunning(true)
	{
		mWindow.AddNotificationSubscriber(this);
	}

	Game::~Game() throw() {}

	int Game::Start()
	{
		mTimer.Update();
		while (mRunning)
		{
			mTimer.Update();

			mRunning = mWindow.ProcessMessages();
			if (!mRunning)
				break;

			Update(mTimer.GetTimeSinceLastTick().Seconds);
			DrawWrapper(mTimer.GetTimeSinceLastTick().Seconds);
		}

		return mWindow.GetExitValue();
	}

	void Game::Quit()
	{
		PostQuitMessage(0);
	}

	void Game::DrawWrapper(float dt)
	{
		mD3DContext.Clear();
		Draw(dt);
		mD3DContext.SwapBuffers();
	}
}
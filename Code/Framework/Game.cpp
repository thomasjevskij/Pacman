#include "Game.hpp"

namespace Framework
{
	Game::Game(HINSTANCE instance, const ApplicationWindow::Description& windowDescription, const D3DContext::Description& contextDescription)
		: mWindow(instance, windowDescription)
		, mD3DContext(&mWindow, contextDescription)
		, mRunning(true)
	{}

	Game::~Game() throw() {}

	int Game::Start()
	{
		while (mRunning)
		{
			mRunning = mWindow.ProcessMessages();
			if (!mRunning)
				break;

			// TODO: Add Timer class and calculate proper dt
			Update(0.0f);
			DrawWrapper(0.0f);
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
		Draw(mRenderBatch, dt);
		mD3DContext.SwapBuffers();
	}
}
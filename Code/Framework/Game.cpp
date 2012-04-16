#include "Game.hpp"

namespace Framework
{
	Game::Game(HINSTANCE instance, const ApplicationWindow::Description& windowDescription, const D3DContext::Description& contextDescription)
		: mWindow(instance, windowDescription)
		, mD3DContext(&mWindow, contextDescription)
		, mRunning(true)
	{}

	Game::~Game() throw() {}

	void Game::Start()
	{
		while (mRunning)
		{
			mRunning = mWindow.ProcessMessages();

			// TODO: Add Timer class and calculate proper dt
			Update(0.0f);
			DrawWrapper(0.0f);
		}
	}

	void Game::DrawWrapper(float dt)
	{
		mD3DContext.Clear();
		Draw(mRenderBatch, dt);
		mD3DContext.SwapBuffers();
	}
}
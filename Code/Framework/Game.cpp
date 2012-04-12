#include "Game.hpp"

namespace Framework
{
	Game::Game(HINSTANCE instance, const ApplicationWindow::Description& windowDescription, const D3DContext::Description& contextDescription)
		: mWindow(instance, windowDescription)
		, mD3DContext(&mWindow, contextDescription)
	{

	}

	Game::~Game() throw()
	{

	}
}
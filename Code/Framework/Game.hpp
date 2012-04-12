#ifndef GAME_HPP
#define GAME_HPP

#include "ApplicationWindow.hpp"
#include "D3DContext.hpp"

namespace Framework
{
	class RenderBatch;

	class Game
	{
	public:
		Game(HINSTANCE instance, const ApplicationWindow::Description& windowDescription, const D3DContext::Description& contextDescription);
		virtual ~Game() throw();
	protected:
		virtual void Update(float dt) = 0;
		virtual void Draw(RenderBatch& renderBatch, float dt) = 0;
	private:
		ApplicationWindow mWindow;
		D3DContext mD3DContext;
	};
}

#endif
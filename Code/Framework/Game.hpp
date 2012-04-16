#ifndef GAME_HPP
#define GAME_HPP

#include "ApplicationWindow.hpp"
#include "D3DContext.hpp"
#include "RenderBatch.hpp"

namespace Framework
{
	class RenderBatch;

	class Game
	{
	public:
		Game(HINSTANCE instance, const ApplicationWindow::Description& windowDescription, const D3DContext::Description& contextDescription);
		virtual ~Game() throw();

		void Start();
	protected:
		virtual void Update(float dt) = 0;
		virtual void Draw(RenderBatch& renderBatch, float dt) = 0;
	private:
		bool mRunning;
		ApplicationWindow mWindow;
		D3DContext mD3DContext;
		RenderBatch mRenderBatch;

		void DrawWrapper(float dt);

		Game(const Game&);
		Game& operator=(const Game&);
	};
}

#endif
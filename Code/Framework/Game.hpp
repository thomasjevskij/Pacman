#ifndef GAME_HPP
#define GAME_HPP

#include "ApplicationWindow.hpp"
#include "D3DContext.hpp"
#include "RenderBatch.hpp"
#include "GameTime.hpp"

namespace Framework
{
	class RenderBatch;

	class Game : public WindowNotificationSubscriber
	{
	public:
		Game(HINSTANCE instance, const ApplicationWindow::Description& windowDescription, const D3DContext::Description& contextDescription);
		virtual ~Game() throw();

		int Start();
	protected:
		ApplicationWindow mWindow;
		D3DContext mD3DContext;

		virtual void Update(float dt) = 0;
		virtual void Draw(RenderBatch& renderBatch, float dt) = 0;

		void Quit();
	private:
		bool mRunning;
		RenderBatch mRenderBatch;
		Helper::GameTime mTimer;

		void DrawWrapper(float dt);

		Game(const Game&);
		Game& operator=(const Game&);
	};
}

#endif
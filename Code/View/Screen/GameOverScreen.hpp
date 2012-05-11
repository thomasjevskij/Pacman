#ifndef GAME_OVER_SCREEN
#define GAME_OVER_SCREEN

#include "GameScreen.hpp"
#include "ApplicationWindow.hpp"
#include "D3DContext.hpp"
#include "UISurface.hpp"
#include "Sprite.hpp"

namespace View
{
	class GameOverScreen : public GameScreen, public Framework::WindowNotificationSubscriber
	{
	public:
		GameOverScreen(GameScreenHandler* handler, Framework::ApplicationWindow* window, const Framework::D3DContext* D3DContext);
		~GameOverScreen() throw();

		void Update(float dt);
		void Draw(float dt);

		void KeyPressed(Framework::ApplicationWindow* window, int keyCode);
		void KeyReleased(Framework::ApplicationWindow* window, int keyCode);
	private:
		Framework::ApplicationWindow* mWindow;
		const Framework::D3DContext* mD3DContext;

		View::UISurface mUISurface;
		View::Sprite mSprite;
	};
}


#endif
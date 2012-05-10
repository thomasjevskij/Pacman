#ifndef INGAME_SCREEN_HPP
#define INGAME_SCREEN_HPP

#include "GameScreen.hpp"
#include "GameplayHandler.hpp"
#include "GameEventSubscriber.hpp"
#include "ApplicationWindow.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"	// Debug

namespace View
{
	namespace IngameScreenState
	{
		enum IngameScreenState { Pregame, Running, Paused };
	}

	class IngameScreen : public GameScreen, public GameEventSubscriber, public Framework::WindowNotificationSubscriber
	{
	public:
		IngameScreen(GameScreenHandler* handler, ID3D10Device* device, Framework::ApplicationWindow* window);
		~IngameScreen() throw();

		void Update(float dt);
		void Draw(float dt);

		void PelletEaten(Helper::Point2f position);
		void PowerPelletEaten(Helper::Point2f position);
		void PowerPelletEnd();
		void GhostEaten(int index);
		void GhostResurrected(int index);
		void PacmanKilled();
		void GameWon();

		void KeyPressed(Framework::ApplicationWindow* window, int keyCode);
		void KeyReleased(Framework::ApplicationWindow* window, int keyCode);
	private:
		ID3D10Device* mDevice;
		IngameScreenState::IngameScreenState mState;

		Framework::ApplicationWindow* mWindow;
		Model::GameplayHandler mGameplayHandler;
		View::Scene* mScene;
		Resources::Sprite* mSprite;			// Debug
		
		bool mLeftPressed;
		bool mRightPressed;
		bool mDownPressed;
	};
}

#endif
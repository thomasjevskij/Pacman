#ifndef INGAME_SCREEN_HPP
#define INGAME_SCREEN_HPP

#include "GameScreen.hpp"
#include "GameplayHandler.hpp"
#include "GameEventSubscriber.hpp"
#include "ApplicationWindow.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"	// Debug
#include "SpriteFont.hpp"
#include "UISurface.hpp"

namespace View
{
	namespace IngameScreenState
	{
		enum IngameScreenState { Pregame, Running, Paused };
	}

	class IngameScreen : public GameScreen, public GameEventSubscriber
	{
	public:
		IngameScreen(GameScreenHandler* handler, Framework::ApplicationWindow* window, const Framework::D3DContext* D3DContext);
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

	private:
		IngameScreenState::IngameScreenState mState;

		Framework::ApplicationWindow* mWindow;
		const Framework::D3DContext* mD3DContext;

		Model::GameplayHandler mGameplayHandler;
		View::Scene* mScene;
		View::UISurface mUISurface;
		View::Sprite mSprite;				// Debug
		View::SpriteFont mSpriteFont;
		
	};
}

#endif
#include "IngameScreen.hpp"

namespace View
{
	IngameScreen::IngameScreen(GameScreenHandler* handler, ID3D10Device* device, Framework::ApplicationWindow* window)
		: GameScreen(handler)
		, mDevice(device)
		, mState(IngameScreenState::Running)	// Debug, start running immediately during testing
		, mWindow(window)
		, mScene(NULL)
	{

		mScene = new View::Scene(mDevice, mGameplayHandler.GetLevel(), mWindow);
		mSprite = Resources::SpriteResourceManager::Instance().Load("pacManTexture.png");
	}

	IngameScreen::~IngameScreen() throw()
	{
		SafeDelete(mScene);
	}

	void IngameScreen::Update(float dt)
	{
		// TODO: Add different logic for different states
		// mGameplayHandler.Update(dt);
		mScene->Update(dt);
	}

	void IngameScreen::Draw(float dt)
	{
		// TODO: Draw different things in different states
		//mSprite->Draw(D3DXVECTOR2(-1.0, -1.0));
		mScene->Draw(dt);
	}

	void IngameScreen::PelletEaten(Helper::Point2f position)
	{
		
	}

	void IngameScreen::PowerPelletEaten(Helper::Point2f position)
	{

	}

	void IngameScreen::PowerPelletEnd()
	{

	}

	void IngameScreen::GhostEaten(int index)
	{

	}

	void IngameScreen::GhostResurrected(int index)
	{

	}

	void IngameScreen::PacmanKilled()
	{

	}

	void IngameScreen::GameWon()
	{
		// TODO: Change to highscore screen
	}

}

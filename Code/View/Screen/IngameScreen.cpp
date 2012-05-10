#include "IngameScreen.hpp"

namespace View
{
	IngameScreen::IngameScreen(GameScreenHandler* handler, Framework::ApplicationWindow* window, const Framework::D3DContext* D3DContext)
		: GameScreen(handler)
		, mState(IngameScreenState::Running)	// Debug, start running immediately during testing
		, mWindow(window)
		, mD3DContext(D3DContext)
		, mScene(NULL)
		, mUISurface(D3DContext->GetDevice())
		, mSprite("pacManTexture.png")			// Debug
	{
		mScene = new View::Scene(mDevice, mGameplayHandler.GetLevel(), mWindow);

		mSprite.SetScale(0.5f);
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
		mScene->Draw(dt);

		mUISurface.Clear();
		// TODO: Draw UI here
		mUISurface.DrawSurface(*mD3DContext);
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

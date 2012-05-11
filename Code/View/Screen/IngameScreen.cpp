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
		, mSpriteFont("font.bmp")
		, mLeftPressed(false)
		, mRightPressed(false)
		, mDownPressed(false)
	{
		mWindow->AddNotificationSubscriber(this);

		mScene = new View::Scene(mD3DContext->GetDevice(), mGameplayHandler.GetLevel(), mWindow, &mGameplayHandler);
		mSprite.SetScale(0.5f);
	}

	IngameScreen::~IngameScreen() throw()
	{
		SafeDelete(mScene);
	}

	void IngameScreen::Update(float dt)
	{
		// TODO: Add different logic for different states
		mGameplayHandler.Update(dt, mLeftPressed, mRightPressed, mDownPressed);
		mScene->Update(dt);
	}

	void IngameScreen::Draw(float dt)
	{
		// TODO: Draw different things in different states
		mScene->Draw(dt);

		mUISurface.Clear();
		// TODO: Draw UI here
		mMap.Draw(mUISurface, mGameplayHandler, D3DXVECTOR2(0, 0), true); 
		//mUISurface.Draw(mSprite);
		mUISurface.Draw(mSpriteFont, D3DXVECTOR2(mMap.GetWidth(mGameplayHandler.GetLevel()), mMap.GetHeight(mGameplayHandler.GetLevel())), "H");

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


	void IngameScreen::KeyPressed(Framework::ApplicationWindow* window, int keyCode) 
	{
		switch (keyCode)
		{
			case VK_LEFT:
				mLeftPressed = true;
			break;

			case VK_RIGHT:
				mRightPressed = true;
			break;

			case VK_DOWN:
				mDownPressed = true;
			break;
		}
	}

	void IngameScreen::KeyReleased(Framework::ApplicationWindow* window, int keyCode)
	{
		switch (keyCode)
		{
			case VK_LEFT:
				mLeftPressed = false;
			break;

			case VK_RIGHT:
				mRightPressed = false;
			break;

			case VK_DOWN:
				mDownPressed = false;
			break;
		}
	}
}

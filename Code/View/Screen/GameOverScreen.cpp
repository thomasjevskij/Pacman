#include "GameOverScreen.hpp"
#include "IngameScreen.hpp"

namespace View
{
	GameOverScreen::GameOverScreen(GameScreenHandler* handler, Framework::ApplicationWindow* window, const Framework::D3DContext* D3DContext)
		: GameScreen(handler)
		, mWindow(window)
		, mD3DContext(D3DContext)
		, mUISurface(mD3DContext->GetDevice())
		, mSprite("game-over-title.png")
	{
		mWindow->AddNotificationSubscriber(this);

		unsigned int viewportWidth = mD3DContext->GetViewportWidth(mD3DContext->GetActiveViewport());
		unsigned int viewportHeight = mD3DContext->GetViewportHeight(mD3DContext->GetActiveViewport());
		
		
		D3DXVECTOR2 titlePosition;
		titlePosition.x = 0.5f * (viewportWidth - mSprite.GetTexture()->GetWidth());
		titlePosition.y = 0.5f * (viewportHeight - mSprite.GetTexture()->GetHeight());
		

		mSprite.SetPosition(titlePosition);
		mSprite.SetScale(2.0f, 2.0f);
		
		//mSprite.SetPosition(D3DXVECTOR2(0, 0));
	}

	GameOverScreen::~GameOverScreen() throw()
	{
		mWindow->RemoveNotificationSubscriber(this);
	}


	void GameOverScreen::Update(float dt)
	{
		
	}

	void GameOverScreen::Draw(float dt)
	{
		mUISurface.Clear();
		mUISurface.Draw(mSprite);
		mUISurface.DrawSurface(*mD3DContext);
	}

	void GameOverScreen::KeyPressed(Framework::ApplicationWindow* window, int keyCode)
	{
		if (keyCode == VK_RETURN)
		{
			mHandler->ChangeScreen(new IngameScreen(mHandler, mWindow, mD3DContext));
		}
	}

	void GameOverScreen::KeyReleased(Framework::ApplicationWindow* window, int keyCode)
	{

	}

}
#include "IngameScreen.hpp"

namespace View
{
	IngameScreen::IngameScreen(GameScreenHandler* handler, Framework::ApplicationWindow* window, const Framework::D3DContext* D3DContext)
		: GameScreen(handler)
		, mState(IngameScreenState::Running)	// Debug, start running immediately during testing
		, mWindow(window)
		, mD3DContext(D3DContext)
		, mCamera(NULL)
		, mCameraController(NULL)
		, mEnvironment(NULL)
		, mSprite("pacManTexture.png")
		, mUISurface(D3DContext->GetDevice())
	{
		Helper::Frustum f;
		f.AspectRatio = static_cast<float>(mWindow->GetClientWidth()) / mWindow->GetClientHeight();
		f.FarDistance = 1000;
		f.FieldOfViewY = D3DX_PI * 0.25;
		f.NearDistance = 1;

		mCamera = new Helper::Camera(f.CreatePerspectiveProjection());
		mCameraController = new Helper::DebugCameraController(D3DXVECTOR3(0, 0, 0), mCamera);
		mEnvironment = new View::Environment(D3DContext->GetDevice(), mGameplayHandler.GetLevel());

		mWindow->AddNotificationSubscriber(mCameraController);

		mSprite.SetPosition(D3DXVECTOR2(80, 80));
		mSprite.SetScale(0.5f);
		mSprite.SetTintColor(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
	}

	IngameScreen::~IngameScreen() throw()
	{
		SafeDelete(mEnvironment);
		SafeDelete(mCameraController);
		SafeDelete(mCamera);
	}

	void IngameScreen::Update(float dt)
	{
		// TODO: Add different logic for different states
		// mGameplayHandler.Update(dt);

		mCameraController->Update(dt);
		mCamera->Commit();
	}

	void IngameScreen::Draw(float dt)
	{
		// TODO: Draw different things in different states
		mEnvironment->Draw(*mCamera);
		
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

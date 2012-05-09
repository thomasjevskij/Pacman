#include "IngameScreen.hpp"

namespace View
{
	IngameScreen::IngameScreen(GameScreenHandler* handler, ID3D10Device* device, Framework::ApplicationWindow* window)
		: GameScreen(handler)
		, mDevice(device)
		, mState(IngameScreenState::Running)	// Debug, start running immediately during testing
		, mWindow(window)
		, mCamera(NULL)
		, mCameraController(NULL)
		, mEnvironment(NULL)
	{
		Helper::Frustum f;
		f.AspectRatio = static_cast<float>(mWindow->GetClientWidth()) / mWindow->GetClientHeight();
		f.FarDistance = 1000;
		f.FieldOfViewY = D3DX_PI * 0.25;
		f.NearDistance = 1;

		mCamera = new Helper::Camera(f.CreatePerspectiveProjection());
		mCameraController = new Helper::DebugCameraController(D3DXVECTOR3(0, 0, 0), mCamera);
		mEnvironment = new View::Environment(mDevice, mGameplayHandler.GetLevel());
		mSprite = Resources::SpriteResourceManager::Instance().Load("pacManTexture.png");

		mWindow->AddNotificationSubscriber(mCameraController);

		mGhost = new View::Ghost(device);
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
		mGhost->Update(dt,Helper::Point2f(0,0),Helper::Point2f(10,0));
		mCameraController->Update(dt);
		mCamera->Commit();
	}

	void IngameScreen::Draw(float dt)
	{
		// TODO: Draw different things in different states
		mEnvironment->Draw(*mCamera);
		//mSprite->Draw(D3DXVECTOR2(-1.0, -1.0));

		mGhost->Draw(dt,mCamera);
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

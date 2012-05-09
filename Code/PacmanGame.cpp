#include "PacmanGame.hpp"
#include "IngameScreen.hpp"

PacmanGame::WindowDescription::WindowDescription()
{
	Description.Caption = "Pacman::Reloaded";
	Description.ClientWidth = 1024;
	Description.ClientHeight = 768;
	Description.Resizable = false;
}

PacmanGame::ContextDescription::ContextDescription()
{
	Description.BackBuffer.Width = 1024;
	Description.BackBuffer.Height = 768;
	Description.Fullscreen = false;
	Description.Viewports.push_back(D3DContext::Viewport());
}

PacmanGame::PacmanGame(HINSTANCE instance)
	: Game(instance, WindowDescription().Description, ContextDescription().Description)
{
	mEffectManager = new Resources::D3DResourceManager<Framework::Effect>(mD3DContext.GetDevice(), "Resources/Effects/");
	mTextureManager = new Resources::D3DResourceManager<Resources::Texture>(mD3DContext.GetDevice(), "Resources/Textures/");
	mModelManager = new Resources::ModelResourceManager("Resources/Objects/", mD3DContext.GetDevice());
	mMaterialManager = new Resources::FileResourceManager<Resources::Material>("Resources/Objects/");
	mLevelManager = new Resources::FileResourceManager<Model::Level>("Resources/Levels/");
	mSoundManager = new Resources::SoundResourceManager("Resources/Sounds/");
	mSpriteManager = new Resources::SpriteResourceManager("Resources/Textures/", mD3DContext.GetDevice());


	mAnimation = new Helper::MorphAnimation(mD3DContext.GetDevice(), animations, timeSpans);	
	
	mCamera = new Helper::Camera(f.CreatePerspectiveProjection(),D3DXVECTOR3(200,0,0),D3DXVECTOR3(0,0,1));
	c = new Helper::DebugCameraControler(D3DXVECTOR3(190,15,160),mCamera);
	p = new Helper::ParticleSystem(mD3DContext.GetDevice(),D3DXVECTOR3(280,15,160),"GhostTrail.fx",D3DXCOLOR(10,0,10,255),1,false,true);

	mWindow.AddNotificationSubscriber(c);

	mSprite = mSpriteManager->Load("whitePixel.png", 0, 0);

	mPacman = new View::Pacman(mD3DContext.GetDevice());

	mScreenHandler.ChangeScreen(new View::IngameScreen(&mScreenHandler, mD3DContext.GetDevice(), &mWindow));

}

PacmanGame::~PacmanGame() throw()
{
	SafeDelete(mEffectManager);
	SafeDelete(mTextureManager);
	SafeDelete(mModelManager);
	SafeDelete(mMaterialManager);
	SafeDelete(mLevelManager);
	SafeDelete(mSoundManager);
	SafeDelete(mSpriteManager);
}

void PacmanGame::Update(float dt)
{
	c->Update(dt);
	mSoundManager->Update();
	mAnimation->Update(dt);
	mSoundManager->Update();
	c->Update(dt);
	mPacman->Update(dt,Helper::Point2f(220,160) ,Model::Coord(0,1));

	mScreenHandler.SwapScreens();
	mScreenHandler.UpdateScreen(dt);

}

void PacmanGame::Draw(float dt)
{

	//mEnvironment->Draw(*mCamera);
	//mAnimation->Draw(*mCamera, D3DXVECTOR3(0,0,0));

	//p->Draw(dt,c->GetCamera());
	//mSprite->Draw(D3DXVECTOR2(0, 0));

	mPacman->Draw(c->GetCamera());

	mScreenHandler.DrawScreen(dt);

}

void PacmanGame::KeyPressed(ApplicationWindow* window, int keyCode)
{
	if (keyCode == VK_ESCAPE)
		Quit();
}

void PacmanGame::KeyReleased(ApplicationWindow* window, int keyCode)
{

}

void PacmanGame::CharEntered(ApplicationWindow* window, char character)
{

}


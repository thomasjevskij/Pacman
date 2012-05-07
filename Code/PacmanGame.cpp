#include "PacmanGame.hpp"
#include "ModelObj.hpp"

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
	Helper::Frustum f;
	f.AspectRatio = static_cast<float>(mWindow.GetClientWidth()) / mWindow.GetClientHeight();
	f.FarDistance = 1000;
	f.FieldOfViewY = D3DX_PI * 0.25;
	f.NearDistance = 1;

	mEffectManager = new Resources::D3DResourceManager<Framework::Effect>(mD3DContext.GetDevice(), "Resources/Effects/");
	mTextureManager = new Resources::D3DResourceManager<Resources::Texture>(mD3DContext.GetDevice(), "Resources/Textures/");
	mObjectManager = new Resources::D3DResourceManager<Resources::ModelObj>(mD3DContext.GetDevice(), "Resources/Objects/");
	mMaterialManager = new Resources::FileResourceManager<Resources::Material>("Resources/Objects/");
	mLevelManager = new Resources::FileResourceManager<Model::Level>("Resources/Levels/");
	mSoundManager = new Resources::SoundResourceManager("Resources/Sounds/");

	// DEBUG
	mSound = mSoundManager->Load("buttonClick.wav");

	Model::Level* aLevel = mLevelManager->Load("Level.png");
	mEnvironment = new View::Environment(mD3DContext.GetDevice(), *aLevel);
	
	mAnimation = new Helper::MorphAnimation(mD3DContext.GetDevice());	
	mCamera = new Helper::Camera(f.CreatePerspectiveProjection(),D3DXVECTOR3(200,0,0),D3DXVECTOR3(0,0,1));
	c = new Helper::DebugCameraControler(D3DXVECTOR3(0,0,-100),mCamera);
	p = new Helper::ParticleSystem(mD3DContext.GetDevice(),D3DXVECTOR3(200,0,0),"GhostTrail.fx",D3DXCOLOR(255,0,0,255),true,true);

	mWindow.AddNotificationSubscriber(c);

	pos = 0;
}

PacmanGame::~PacmanGame() throw()
{
	SafeDelete(mEffectManager);
	SafeDelete(mTextureManager);
	SafeDelete(mLevelManager);
	SafeDelete(mObjectManager);
	SafeDelete(mMaterialManager);
	SafeDelete(mSoundManager);
	SafeDelete(mEnvironment);

	SafeDelete(mAnimation);
	SafeDelete(mCamera);
	SafeDelete(c);
	SafeDelete(p);
}

void PacmanGame::Update(float dt)
{
	c->Update(dt);
	p->SetPosition(D3DXVECTOR3(pos,0,0));
	//pos += 10 * dt;
	//mSoundManager->Update();
	//mAnimation->Update(dt);
}

void PacmanGame::Draw(RenderBatch& renderBatch, float dt)
{
	//mEnvironment->Draw();
	//mAnimation->Draw(*mCamera, D3DXVECTOR3(0,0,0));
	p->Draw(dt,c->GetCamera());
}

void PacmanGame::KeyPressed(ApplicationWindow* window, int keyCode)
{
	if (keyCode == VK_ESCAPE)
		Quit();
	else if (keyCode == VK_F6)
		mSound->Play();
}

void PacmanGame::KeyReleased(ApplicationWindow* window, int keyCode)
{

}

void PacmanGame::CharEntered(ApplicationWindow* window, char character)
{

}


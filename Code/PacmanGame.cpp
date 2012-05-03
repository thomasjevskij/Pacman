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
	mEffectManager = new Resources::D3DResourceManager<Framework::Effect>(mD3DContext.GetDevice(), "Resources/Effects/");
	mTextureManager = new Resources::D3DResourceManager<Resources::Texture>(mD3DContext.GetDevice(), "Resources/Textures/");
	mObjectManager = new Resources::D3DResourceManager<Resources::ModelObj>(mD3DContext.GetDevice(), "Resources/Objects/");
	mMaterialManager = new Resources::FileResourceManager<Resources::Material>("Resources/Objects/");
	mLevelManager = new Resources::FileResourceManager<Model::Level>("Resources/Levels/");
	
	// DEBUG
	mSoundManager = new Resources::SoundResourceManager("Resources/Sounds/");
	mSound = mSoundManager->Load("buttonClick.wav");

	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH( &proj, D3DX_PI/2, 1, 0, 500 );
	mCamera = new Helper::Camera(proj,D3DXVECTOR3(200,0,0),D3DXVECTOR3(0,0,1));

	Helper::Frustum f;
	f.AspectRatio = 1;
	f.FarDistance = 500;
	f.NearDistance = 0;
	f.FieldOfViewY = D3DX_PI/2;
	c = new Helper::DebugCameraControler(D3DXVECTOR3(0,0,-100),mCamera);
	p = new Helper::ParticleSystem(mD3DContext.GetDevice(),D3DXVECTOR3(200,0,0),"GhostTrail.fx",D3DXCOLOR(0,255,0,255),false,true);

	mWindow.AddNotificationSubscriber(c);

	pos = 0;

	//mPellet = mObjectManager->Load("pellet.obj");
}

PacmanGame::~PacmanGame() throw()
{
	SafeDelete(mEffectManager);
	SafeDelete(mLevelManager);
	SafeDelete(mObjectManager);
	SafeDelete(mMaterialManager);
	SafeDelete(mSoundManager);
}

void PacmanGame::Update(float dt)
{
	c->Update(dt);
	p->SetPosition(D3DXVECTOR3(pos,0,0));
	pos += 10 * dt;
	mSoundManager->Update();
}

void PacmanGame::Draw(RenderBatch& renderBatch, float dt)
{
	p->Draw(dt,c->GetCamera());
	//mPellet->Draw(D3DXVECTOR3(0, 0, 0));
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


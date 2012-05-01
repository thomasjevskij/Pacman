#include "PacmanGame.hpp"

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
	mEffectManager = new Resources::EffectResourceManager("Resources/Effects/", mD3DContext.GetDevice());
	mLevelManager = new Resources::FileResourceManager<Model::Level>("Resources/Levels/");
	
	// DEBUG
	mSoundManager = new Resources::SoundResourceManager("Resources/Sounds/");
	mSound = mSoundManager->Load("buttonClick.wav");

	Helper::Frustum f;
	f.AspectRatio = 1;
	f.FarDistance = 500;
	f.NearDistance = 0;
	f.FieldOfViewY = D3DX_PI/2;
	c = new Helper::Camera(f.CreatePerspectiveProjection(),D3DXVECTOR3(0,0,-50),D3DXVECTOR3(0,0,1));
	p = new Helper::ParticleSystem(mD3DContext.GetDevice(),D3DXVECTOR3(0,0,0),"GhostTrail.fx",D3DXCOLOR(255,0,255,100));
}

PacmanGame::~PacmanGame() throw()
{
	SafeDelete(mEffectManager);
	SafeDelete(mLevelManager);
}

void PacmanGame::Update(float dt)
{
	
}

void PacmanGame::Draw(RenderBatch& renderBatch, float dt)
{
	p->Draw(dt,*c);
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


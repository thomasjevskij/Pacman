#include "PacmanGame.hpp"
#include "IngameScreen.hpp"
#include "GameOverScreen.hpp"

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
	//mModelManager = new Resources::ModelResourceManager("Resources/Objects/", mD3DContext.GetDevice());
	mModelManager = new Resources::D3DResourceManager<Resources::StaticModelData>(mD3DContext.GetDevice(), "Resources/Objects/");
	mMaterialManager = new Resources::FileResourceManager<Resources::Material>("Resources/Objects/");
	mLevelManager = new Resources::FileResourceManager<Model::Level>("Resources/Levels/");
	mSoundManager = new Resources::SoundResourceManager("Resources/Sounds/");

	mScreenHandler.ChangeScreen(new View::IngameScreen(&mScreenHandler, &mWindow, &mD3DContext));
	//mScreenHandler.ChangeScreen(new View::GameOverScreen(&mScreenHandler, &mWindow, &mD3DContext));
}

PacmanGame::~PacmanGame() throw()
{
	SafeDelete(mEffectManager);
	SafeDelete(mTextureManager);
	SafeDelete(mModelManager);
	SafeDelete(mMaterialManager);
	SafeDelete(mLevelManager);
	SafeDelete(mSoundManager);
}

void PacmanGame::Update(float dt)
{
	mSoundManager->Update();

	mScreenHandler.UpdateScreen(dt);
	mScreenHandler.SwapScreens();
}

void PacmanGame::Draw(float dt)
{
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


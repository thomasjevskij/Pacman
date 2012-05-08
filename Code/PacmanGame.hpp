#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include "Game.hpp"
#include "FileResourceManager.hpp"
#include "D3DResourceManager.hpp"
#include "Effect.hpp"
#include "Level.hpp"
#include "ModelObj.hpp"
#include "Sound2D.hpp" // DEBUG
#include "Environment.hpp" // DEBUG
#include "MorphAnimation.hpp"
#include "Camera.hpp"
#include "ParticleSystem.hpp"
#include "DebugCameraControler.hpp"
#include "Sprite.hpp"

using namespace Framework;

class PacmanGame : public Game
{
public:
	PacmanGame(HINSTANCE instance);
	~PacmanGame() throw();

	void KeyPressed(ApplicationWindow* window, int keyCode);
	void KeyReleased(ApplicationWindow* window, int keyCode);
	void CharEntered(ApplicationWindow* window, char character);
	
protected:
	void Update(float dt);
	void Draw(float dt);

private:
	struct WindowDescription
	{
		ApplicationWindow::Description Description;

		WindowDescription();
	};

	struct ContextDescription
	{
		D3DContext::Description Description;

		ContextDescription();
	};

	Resources::D3DResourceManager<Framework::Effect>* mEffectManager;
	Resources::D3DResourceManager<Resources::Texture>* mTextureManager;
	Resources::D3DResourceManager<Resources::ModelObj>* mObjectManager;
	Resources::FileResourceManager<Resources::Material>* mMaterialManager;
	Resources::FileResourceManager<Model::Level>* mLevelManager;
	Resources::SoundResourceManager* mSoundManager;
	Resources::SpriteResourceManager* mSpriteManager;

	// Debug
	Resources::Sprite* mSprite;
	Resources::Sound2D* mSound;
	View::Environment* mEnvironment;
	
	Helper::MorphAnimation* mAnimation;
	Helper::ParticleSystem* p;

	Helper::Camera* mCamera;
	Helper::DebugCameraControler *c;
	float pos;
};

#endif
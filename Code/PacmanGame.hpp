#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include "Game.hpp"
#include "FileResourceManager.hpp"
#include "Effect.hpp"
#include "Level.hpp"
#include "ModelObj.hpp"
#include "Sound2D.hpp" // DEBUG

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
	void Draw(RenderBatch& renderBatch, float dt);

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

	Resources::EffectResourceManager* mEffectManager;
	Resources::FileResourceManager<Model::Level>* mLevelManager;
	Resources::FileResourceManager<Resources::ModelObj>* mObjectManager;
	Resources::FileResourceManager<Resources::Material>* mMaterialManager;
	
	// DEBUG
	Resources::SoundResourceManager* mSoundManager;
	Resources::Sound2D* mSound;
};

#endif
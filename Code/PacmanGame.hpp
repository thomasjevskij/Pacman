#ifndef PACMAN_GAME_HPP
#define PACMAN_GAME_HPP

#include "Game.hpp"

using namespace Framework;

class PacmanGame : public Game
{
public:
	PacmanGame(HINSTANCE instance);

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
};

#endif
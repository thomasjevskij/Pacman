#ifndef GAMEPLAYHANDLER_HPP
#define GAMEPLAYHANDLER_HPP

#include "Level.hpp"
#include "LevelHandler.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Fruit.hpp"
#include "Ghost.hpp"
#include "GameTime.hpp"
#include <vector>

namespace Model
{
	class GameplayHandler
	{
	public:
		GameplayHandler();
		void Update(float dt);
		GameObject GetPacman();
		std::vector<Ghost> GetGhosts();
		Level GetLevel();
		int GetCurrentlevelIndex();
		int GetLives();
		int GetScore();
		//Time GetTimeLeft();
	private:
		LevelHandler mLevelHandler;
		Level mLevel;
		Player mPlayer;
		bool mLevelWasWon;
		bool mGameRestart;
		std::vector<Ghost> mGhosts;
		int mLives, mCurrentLevel, mScore;
		bool TestGridCollision(Coord objectPos1, Coord objectPos2);
		bool TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos);
		void NewLevel();
		void ResetGame();


	};
}










#endif
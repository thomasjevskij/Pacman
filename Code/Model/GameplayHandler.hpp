#ifndef GAMEPLAYHANDLER_HPP
#define GAMEPLAYHANDLER_HPP

#include "Level.hpp"
#include "LevelHandler.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Fruit.hpp"
#include "Ghost.hpp"
#include "GameTime.hpp"
#include "
#include <vector>

namespace Model
{
	class GameplayHandler
	{
	public:
		GameplayHandler();
		void Update(float dt);
		GameObject GetPacman() const;
		std::vector<Ghost> GetGhosts() const;
		Level GetLevel() const;
		int GetCurrentlevelIndex() const;
		int GetLives() const;
		int GetScore() const;
		float GetTimeLeft() const;
	private:
		LevelHandler mLevelHandler;
		Level mLevel;
		Player mPlayer;
		Fruit* mFruit;
		bool mLevelWasWon;
		bool mGameRestart;
		std::vector<Ghost> mGhosts;
		int mLives, mCurrentLevel, mScore;
		float mGameTime;
		bool TestGridCollision(Coord objectPos1, Coord objectPos2);
		bool TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos);
		void NewLevel();
		void ResetGame();


	};
}










#endif
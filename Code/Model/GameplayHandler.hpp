#ifndef GAMEPLAYHANDLER_HPP
#define GAMEPLAYHANDLER_HPP

#include "Level.hpp"
#include "LevelHandler.hpp"
#include "Player.hpp"
#include "Fruit.hpp"
#include "Ghost.hpp"
#include "GameTime.hpp"
#include "GameEventSubscriber.hpp"
#include <vector>

namespace Model
{
	class GameplayHandler
	{
	public:
		GameplayHandler();
		void Update(float dt);

		Player GetPacman() const;
		std::vector<Ghost> GetGhosts() const;
		Level GetLevel() const;
		int GetCurrentlevelIndex() const;
		int GetLives() const;
		int GetScore() const;
		float GetTimeLeft() const;
	private:
		LevelHandler mLevelHandler;
		View::GameEventSubscriber* mGameEventSubscriber;
		Level mLevel;
		Player mPlayer;
		Fruit mFruit;
		std::vector<Ghost> mGhosts;

		bool mLevelWasWon;
		bool mGameRestart;
		int mLives, mCurrentLevel, mScore, mPelletsEaten;
		float mGameTime;

		bool TestGridCollision(Coord objectPos1, Coord objectPos2);
		bool TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos);
		void NewLevel();
		void ResetGame();


	};
}


#endif
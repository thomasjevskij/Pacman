#ifndef GAMEPLAYHANDLER_HPP
#define GAMEPLAYHANDLER_HPP

#include "Level.hpp"
#include "LevelHandler.hpp"
#include "Player.hpp"
#include "Fruit.hpp"
#include "Ghost.hpp"
#include "GameTime.hpp"
#include "GameEventSubscriber.hpp"
#include "ModelDataInterface.hpp"
#include <vector>

namespace Model
{
	class GameplayHandler : public ModelDataInterface
	{
	public:
		GameplayHandler();
		void Update(float dt, bool leftPressed, bool rightPressed, bool backPressed);

		Helper::Point2f GetPacmanPosition() const;
		Helper::Point2f GetPacmanFacing() const;
		std::vector<Helper::Point2f> GetGhostPositions() const;

		Player GetPacman() const;
		std::vector<Ghost> GetGhosts() const;
		const Level& GetLevel();
		int GetCurrentLevelIndex() const;
		int GetLives() const;
		int GetScore() const;
		float GetTimeLeft() const;
	private:
		LevelHandler mLevelHandler;
		View::GameEventSubscriber* mGameEventSubscriber;
		//Level mLevel;
		Player mPlayer;
		Fruit mFruit;
		std::vector<Ghost> mGhosts;

		bool mLevelWasWon;
		bool mGameRestart;
		int mLives, mCurrentLevel, mScore, mPelletsEaten;
		float mGameTime, mPowerModeTimer;

		bool TestGridCollision(Coord objectPos1, Coord objectPos2);
		bool TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos);
		void NewLevel();
		void ResetGame();

	};
}


#endif
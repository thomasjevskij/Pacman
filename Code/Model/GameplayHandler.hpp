#ifndef GAMEPLAYHANDLER_HPP
#define GAMEPLAYHANDLER_HPP

#include "Level.hpp"
#include "LevelHandler.hpp"
#include "GameObject.hpp"
#include "Player.hpp"
#include "Fruit.hpp"
#include "Ghost.hpp"
#include <vector>

namespace Model
{
	class GameplayHandler
	{
	public:
		GameplayHandler();
		void Update();
		//GameObject GetPacman();
		//vector<GameObject> GetGhosts();
		Level GetLevel();
		int GetCurrentlevelIndex();
		int GetLives();
		int GetScore();
		//Time GetTimeLeft();
	private:
		LevelHandler mLevelHandler;
		Level mLevel;
		//Player player;
		//vector<Ghost> ghosts;
		//Timer timer
		int mLives, mCurrentLevel, mScore;
		bool TestGridCollision(Coord objectPos1, Coord objectPos2);
		bool TestRealCollision(Coord ghostRealPos, Coord pacmanRealPos);


	};
}










#endif
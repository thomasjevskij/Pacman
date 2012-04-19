#ifndef GAMEPLAYHANDLER_HPP
#define GAMEPLAYHANDLER_HPP

#include "Level.hpp"
#include <vector>

namespace Model
{
	class GameplayHandler
	{
	private:
		//LevelHandler levelHandler;
		Level level;
		//Player player;
		//vector<Ghost> ghosts;
		//Timer timer
		int lives, currentLevel, score;
	public:
		void Initialize();
		void Update();
		//GameObject GetPacman();
		//vector<GameObject> GetGhost();
		//vector<Coord> GetPellets();
		//vector<Coord> GetPowerPellets();
		Level GetLevel();
		int GetCurrentlevelIndex();
		int GetLives();
		int GetScore();
		//Time GetTimeLeft();

	}
}










#endif
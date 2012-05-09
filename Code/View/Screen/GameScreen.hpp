#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

namespace View
{
	class GameScreen;
	class GameScreenHandler;

	class GameScreenHandler
	{
	public:
		GameScreenHandler();
		GameScreenHandler(GameScreen* startScreen);
		~GameScreenHandler() throw();

		void ChangeScreen(GameScreen* newScreen);
		void UpdateScreen(float dt);
		void DrawScreen(float dt);

		void SwapScreens();
	private:
		GameScreen* mCurrentScreen;
		GameScreen* mNextScreen;

		GameScreenHandler(const GameScreenHandler&);
		GameScreenHandler& operator=(const GameScreenHandler&);
	};

	class GameScreen
	{
	public:
		GameScreen(GameScreenHandler* handler);
		virtual ~GameScreen() throw();

		virtual void Update(float dt) = 0;
		virtual void Draw(float dt) = 0;
	protected:
		GameScreenHandler* mHandler;
	};

	
}

#endif
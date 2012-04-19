#ifndef GAMETIME_HPP
#define GAMETIME_HPP

#include <Windows.h>

namespace Helper
{
	struct Time
	{
		double Milliseconds;
		double Seconds;
	};

	class GameTime
	{
	public:
		GameTime();
		~GameTime();
		void Update();
		Time GetTimeSinceLastTick();
		Time GetTimeSinceGameStart();
		void StartFPSCount(float intervalSeconds);
		void EndFPSCount();
		float GetFPS();

	private:
		__int64		mPrevTimeStamp;
		__int64		mGameStartTime;

		double		mMilliSecondsPerTick;
		bool		mCalculateFPS;
		float		mFPSInterval;
		float		mFPS;
		int			mFrameCount;
		float		mFPSElapsedS;

		Time		mElapsedSinceStart;
		Time		mElapsedSinceLastTick;
	};
}
#endif
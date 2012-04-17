#include "GameTime.hpp"

namespace Framework
{
	// Constructor - initialize the game time, set start values for teh time stamps and calculate the length of a tick
	GameTime::GameTime() 
		: mPrevTimeStamp(0), mGameStartTime(0), mMilliSecondsPerTick(0.0), mCalculateFPS(false), mFPSInterval(1.0f),
		  mFPS(0.0f), mFrameCount(0), mFPSElapsedS(0.0f)
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		mMilliSecondsPerTick = 1000.0 / (double)countsPerSec;

		QueryPerformanceCounter((LARGE_INTEGER*)&mGameStartTime);
		Update();
	}

	GameTime::~GameTime()
	{
	}

	// Update the game time by calculating new values for elapsed time and getting new time stamp values
	void GameTime::Update()
	{
		__int64 currTimeStamp = 0;
		QueryPerformanceCounter((LARGE_INTEGER*) & currTimeStamp);

		mElapsedSinceLastTick.Milliseconds = (currTimeStamp - mPrevTimeStamp) * mMilliSecondsPerTick;
		mElapsedSinceLastTick.Seconds = mElapsedSinceLastTick.Milliseconds * 0.001;

		mElapsedSinceStart.Milliseconds = (currTimeStamp - mGameStartTime) * mMilliSecondsPerTick;
		mElapsedSinceStart.Seconds = mElapsedSinceStart.Milliseconds * 0.001;

		if(mCalculateFPS)
		{
			mFrameCount++;
			mFPSElapsedS += mElapsedSinceLastTick.Seconds;

			if(mFPSElapsedS >= mFPSInterval)
			{
				mFPS = mFrameCount / mFPSInterval;
				mFrameCount = 0;
				mFPSElapsedS -= mFPSInterval;
			}
		}

		mPrevTimeStamp = currTimeStamp;
	}

	// Get the time elapsed since last update
	Time GameTime::GetTimeSinceLastTick()
	{
		return mElapsedSinceLastTick;
	}

	// Get the time elapsed since the game started
	Time GameTime::GetTimeSinceGameStart()
	{
		return mElapsedSinceStart;
	}

	void GameTime::StartFPSCount(float intervalSeconds)
	{
		mCalculateFPS = true;
		mFPSInterval = intervalSeconds;
		mFPS = 0;
	}

	void GameTime::EndFPSCount()
	{
		mCalculateFPS = false;
		mFPSInterval = 1;
	}

	float GameTime::GetFPS()
	{
		return mFPS;
	}
}
#include "Time.h"

#include "Util/Logger.h"

#include <SDL2/SDL.h>

#include <numeric>

const int deltasSize = 100;

Time::Time()
{
	mDesiredFrameTime = 1000.0f / mDesiredFrameRate;
	mStartTicks = SDL_GetTicks();
}

Time::~Time()
{
	
}

void Time::FrameStart()
{
	mNow = SDL_GetPerformanceCounter();
	mElapsedTicks = mNow - mLastTime;
	mFrequency = static_cast<float>(SDL_GetPerformanceFrequency());
	mDeltaTime = static_cast<float>(mElapsedTicks) / mFrequency * 1000.0f;
}

void Time::FrameEnd()
{
	mLastTime = mNow;

	//Update FPS every second
	mFrameCount++;
	if (SDL_GetTicks() - mStartTicks >= 1000)
	{
		mFPS = mFrameCount;
		mFrameCount = 0;
		mStartTicks = SDL_GetTicks();
	}
}

void Time::SetDesiredFrameRate(int desiredFPS)
{
	mDesiredFrameRate = desiredFPS;
	mDesiredFrameTime = 1000.0f / mDesiredFrameRate;
}

bool Time::frameLimit(bool limit)
{
	if (!limit) { return false; }
	if(mDeltaTime < mDesiredFrameTime)
	{
		SDL_Delay(static_cast<Uint32>(mDesiredFrameTime - mDeltaTime));
		return true;
	}
	return false;
}

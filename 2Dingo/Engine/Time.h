#pragma once
#include <stdint.h>
#include <vector>

class Time
{
public:
	Time();
	~Time();

	// Sets the timings at the start of the frame/gameloop
	void FrameStart();
	// Ends the timings
	void FrameEnd();
	// Returns the delta time as float
	float getDeltaTime() { return mDeltaTime; }

	//////////////////////////////////////////////////
	// Sets the desired framerate for frame limiting
	void SetDesiredFrameRate(int desiredFPS);
	// Does artificial delay with SDL_Delay to try limit FPS
	bool frameLimit(bool limit);
	// Returns the FPS
	int getFPS() { return mFPS; }


private:
	int mDesiredFrameRate = 60;
	float mDesiredFrameTime = 0.0f;
	uint32_t mStartTicks;
	int mFrameCount = 0;
	int mFPS = 0;

private:
	uint64_t mNow = 0;
	uint64_t mElapsedTicks = 0;
	uint64_t mLastTime = 0;
	float mFrequency = 0.0f;
	float mDeltaTime = 0.0f;
};
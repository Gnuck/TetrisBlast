#include "Timer.h"



Timer::Timer()
{
	startTime = 0;
	pausedTime = 0;

	mPaused = false;
	mStarted = false;
}


Timer::~Timer(){}

void Timer::start() {

	mStarted = true;
	mPaused = false;

	startTime = SDL_GetTicks();
	pausedTime = 0;
}

void Timer::stop() {
	mStarted = false;
	mPaused = false;

	startTime = 0;
	pausedTime = 0;
}

void Timer::pause() {
	if (mStarted && !mPaused) {
		mPaused = true;
		pausedTime = SDL_GetTicks() - startTime;
		startTime = 0;
	}
}

Uint32 Timer::getTime() {
	Uint32 time = 0;
	if (mStarted) {
		if (mPaused) {
			time = pausedTime;
		}
		else {
			time = SDL_GetTicks() - startTime;
		}
	}
	return time;
}

bool Timer::timerStarted() {
	return mStarted;
	
}

bool Timer::timerPaused() {
	return mPaused && mStarted;
}
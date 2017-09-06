#pragma once
#include <SDL.h>
class Timer
{
public:
	Timer();
	~Timer();

	//clock actions
	void start();
	void pause();
	void unpause();
	void stop();

	//clock status checks
	bool timerStarted();
	bool timerPaused();

	//get time since start of timer
	Uint32 getTime();

private:
	
	//start time
	Uint32 startTime;

	//time when timer was paused
	Uint32 pausedTime;

	//timer status
	bool mPaused=false;
	bool mStarted=false;
};


#include "GameTimer.h"
#include <SDL.h>


GameTimer::GameTimer()
{
	secondsPerCount = 0.0;
	deltaTime = -1.0;
	baseTime = 0;
	pausedTime = 0;
	prevTime = 0;
	curTime = SDL_GetTicks();
	stopTime = 0;
	stopped = false;
}


GameTimer::~GameTimer()
{
}

void GameTimer::Tick()
{
	if (stopped)
	{
		deltaTime = 0.0;
		return;
	}
	//Get the time this frame
	curTime = SDL_GetTicks();

	//Time difference between this frame and the last
	deltaTime = (float)(curTime - prevTime)/60;
	//Prepare for next frame.
	prevTime = curTime;

	//Negative check on change of power mode or processor.
	if (deltaTime < 0.0)
	{
		deltaTime = 0.0;
	}
}

void GameTimer::Reset()
{
	baseTime = SDL_GetTicks();
	prevTime = SDL_GetTicks();
	stopTime = 0;
	stopped = false;
}

void GameTimer::Stop()
{
	//If the timer is stopped then don't do anything
	if (!stopped)
	{
		//Save the time we stopped at, and set the Boolean that we stopped
		stopTime = SDL_GetTicks();;
		stopped = true;
	}
}

void GameTimer::Start()
{
	unsigned int startTime = SDL_GetTicks();

	//Accumulate the time that elapsed from Stop and Start pairs.

	//If we are restoring from a paused state...
	if (stopped)
	{
		pausedTime += (startTime - stopTime);

		//PrevTime becomes obsolete since we are Unpausing game
		prevTime = startTime;

		//Reset stop values
		stopTime = 0;
		stopped = false;
	}
}

float GameTimer::TotalTime() const
{
	//return elapsed time EXCLUDING paused and stopped time

	if (stopped)
	{
		return (float)(((stopped - pausedTime) - baseTime)*secondsPerCount);
	}
	else
	{
		return (float)(((curTime - pausedTime) - baseTime)*secondsPerCount);
	}
}

float GameTimer::DeltaTime()const
{
	return (float)deltaTime;
}
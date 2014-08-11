#pragma once
class GameTimer
{
public:
	GameTimer();
	~GameTimer();

	float TotalTime()const; //in seconds
	float DeltaTime() const; //in seconds

	void Reset(); //Call before message loop.
	void Start(); //Call when unpaused.
	void Stop(); //Call when paused.
	void Tick(); //Call every frame.

private:
	double secondsPerCount;
	double deltaTime;
	int baseTime;
	int pausedTime;
	int prevTime;
	int curTime;
	int stopTime;

	bool stopped;
};


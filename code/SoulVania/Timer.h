#pragma once

#include "Stopwatch.h"

class Timer
{
public:
	// interval in seconds
	Timer(int startingTime = 0);

	void AddCounter(int counter);
	void SetCounter(int counter);
	void ResetLastSecond();
	int GetCounter() const;

	bool CountDown();

private:
	int counter;
	Stopwatch stopwatch;
};
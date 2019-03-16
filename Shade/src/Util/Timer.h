#pragma once
#include <chrono>

class Timer
{
public:
	Timer();

	void reset();
	float getTimeElapsed();

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> starting_time;
};
#include "Timer.h"

Timer::Timer()
{
	reset();
}

void Timer::reset()
{
	starting_time = std::chrono::high_resolution_clock::now();
}

float Timer::getTimeElapsed()
{
	auto now = std::chrono::high_resolution_clock::now();
	return std::chrono::duration<float, std::ratio<1,1>>(now - starting_time).count();
}
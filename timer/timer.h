#pragma once
#include <chrono>
class timer
{
private:
protected:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	long long duration = 0;

public:
	void StartTimer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	void EndTimer()
	{
		end = std::chrono::high_resolution_clock::now();
	}
	auto ElapsedInNanoSeconds()
	{
		duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		return duration;
	}
	auto ElapsedInMicroSeconds()
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	}

	auto ElapsedInMilliSeconds()
	{
		return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	}

	auto ElapsedInSeconds()
	{
		return std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
	}
};

class timer_average:timer
{
private:
	int timesCollected = 0;
	int timeArrayIndex = 0;
	long long allTimes[];
public:
	
	void howManyTimesCollected(int amount)
	{
		timesCollected = amount;
	}
	void StoreTime()
	{
		
	}
};
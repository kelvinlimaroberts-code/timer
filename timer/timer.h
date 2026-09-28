#pragma once
#include <chrono>
class timer
{
private:
protected:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	long long elapsed = 0;

public:
	void StartTimer()
	{
		start = std::chrono::high_resolution_clock::now();
	}
	void EndTimer()
	{
		end = std::chrono::high_resolution_clock::now();
	}
	long long ElapsedInNanoSeconds()
	{
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		return elapsed;
	}
	long long ElapsedInMicroSeconds()
	{
		elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		return elapsed;
	}

	long long ElapsedInMilliSeconds()
	{
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		return elapsed;
	}

	long long ElapsedInSeconds()
	{
		elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		return elapsed;
	}
};

class timer_average : public timer
{
private:
	int timesCollected = 0;
	long long totalTime = 0;
	long long averageTime = 0;
	long long minTime = 9223372036854775807;
	long long maxTime = 0;

public:
	void StoreTime()
	{
		timesCollected++;
		totalTime += elapsed;
		if (elapsed < minTime)
		{
			minTime = elapsed;
		}
		if (elapsed > maxTime)
		{
			maxTime = elapsed;
		}
	}
	long long Average()
	{
		averageTime = totalTime / timesCollected;
		return averageTime;
	}
	long long TimeMin()
	{
		return minTime;
	}

	long long TimeMax()
	{
		return maxTime;
	}
};
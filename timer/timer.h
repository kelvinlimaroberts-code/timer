#pragma once
#include <chrono>
#include <fstream>
class timer
{
private:
protected:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	enum UnitTypes {NANO, MICRO, MILLI, SEC};
	UnitTypes unit = NANO;
	long long elapsed = 0;
	bool timerEnded = false;
public:
	void StartTimer()
	{
		start = std::chrono::high_resolution_clock::now();
		timerEnded = false;
	}
	void EndTimer()
	{
		end = std::chrono::high_resolution_clock::now();
		timerEnded = true;
	}
	long long ElapsedInNanoSeconds()
	{
		elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
		unit = NANO;
		return elapsed;
	}
	long long ElapsedInMicroSeconds()
	{
		elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
		unit = MICRO;
		return elapsed;
	}

	long long ElapsedInMilliSeconds()
	{
		elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		unit = MILLI;
		return elapsed;
	}

	long long ElapsedInSeconds()
	{
		elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
		unit = SEC;
		return elapsed;
	}
};

class timer_average : public timer
{
private:
	const int howManyTimeSlotsPossible = 999999;
protected:
	long long timesArray[999999]; //how many time
	int timesCollected = 0;
	long long totalTime = 0;
	long long averageTime = 0;
	long long minTime = 0;
	long long maxTime = 0;
public:
	void StoreTime()
	{
		if (timesCollected < howManyTimeSlotsPossible)
		{
			timesArray[timesCollected] = elapsed;
			timesCollected++;
		}
	}
	void CalculateOutputs()
	{
		minTime = timesArray[0];
		maxTime = timesArray[0];
		for (int i = 1; i < timesCollected; i++)
		{
			totalTime += timesArray[i];
			if (timesArray[i] < minTime)
			{
				minTime = timesArray[i];
			}
			else if (timesArray[i] > maxTime)
			{
				maxTime = timesArray[i];
			}
		}
		averageTime = totalTime / timesCollected;
	}
	long long Average()
	{
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

	std::string getUnit()
	{
		std::string out;
		switch (unit)
		{
		case NANO:
			out = "nanoseconds";
			break;

		case MICRO:
			out = "microseconds";
			break;

		case MILLI:
			out = "milliseconds";
			break;

		case SEC:
			out = "seconds";
			break;

		default:
			out = "?";
		}
		return out;
	}
};


class timer_file : public timer_average
{
private:
	std::string fileEnd = ".csv";
public:
	void PrintToFile(std::string FileName = "CodeTimerOutputs")
	{
		if (timerEnded)
		{
			std::string fullFileName = FileName + fileEnd;
			std::ofstream OutputFile(fullFileName);  //open file
			OutputFile << "frame, time (" << getUnit() << ')';
			for (int i = 0; i < timesCollected; i++)
			{
				OutputFile << '\n' << i << ',' << timesArray[i];
			}
			OutputFile << "\n\n";
			OutputFile.close();  //close file
		}
	}
	
};
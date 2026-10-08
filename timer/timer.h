#pragma once
#include <chrono>
#include <fstream>
#include <iostream>

class Timer
{
private:
protected:
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	enum UnitTypes { NANO, MICRO, MILLI, SEC };
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

class Timer_Average : public Timer
{
private:
	const static int howManyTimeSlotsPossible = 9999;
	bool calculatedOutputs = false;
protected:
	long timesArray[howManyTimeSlotsPossible]; //how many time
	int timesCollected = 0;
	long totalTime = 0;
	long averageTime = 0;
	long minTime = 0;
	long maxTime = 0;
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
		calculatedOutputs = true;
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

	void OutputResults()
	{
		if (!calculatedOutputs) CalculateOutputs();
		std::cout << "\n\n"
			<< "\naverage," << Average() << ' ' << getUnit()
			<< "\nmin," << TimeMin() << ' ' << getUnit()
			<< "\nmax," << TimeMax() << ' ' << getUnit()
			<< "\n\n";
	}
};


class Timer_File : public Timer_Average
{
private:
	bool hasPrinted = false;
public:
	void PrintToFile(std::string FileName = "CodeTimerOutputs.csv")
	{
		if (timerEnded)
		{
			CalculateOutputs();
			std::string fullFileName = FileName;
			std::ofstream OutputFile(fullFileName);  //open file
			OutputFile << "frame, time (" << getUnit() << ')';
			for (int i = 0; i < timesCollected; i++)
			{
				OutputFile << '\n' << i << ',' << timesArray[i];
			}
			OutputFile << "\n\n";
			OutputFile << "\naverage," << Average();
			OutputFile << "\nmin," << TimeMin();
			OutputFile << "\nmax," << TimeMax();
			OutputFile.close();  //close file
		}
	}

	void CheckPrint(int desiredAmountOfTimesInfo, std::string FileName)
	{
		if (hasPrinted == false && (timesCollected >= desiredAmountOfTimesInfo))
		{
			PrintToFile(FileName);
			hasPrinted = true;
		}
	}
};
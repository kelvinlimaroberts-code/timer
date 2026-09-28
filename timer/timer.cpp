#include <iostream>
#include "timer.h"
const int NUM_LOOPS = 1000;
int integer = 765;
float floateger = 87346.7635;
double doublager = 173264.821368;
long longeger = 23456789;
long long coutTimeAverage = 0;
long long coutTimeMin = 0;
long long coutTimeMax = 0;
long long printFTimeAverage = 0;
long long printFTimeMin = 0;
long long printFTimeMax = 0;


void useCOut()
{
    timer_average dt;
    for (int i = 0; i < NUM_LOOPS; i++)
    {
        dt.StartTimer();
        std::cout << "\nI am using C Out right now. I like numbers."
            << "\nmy integer: " << integer
            << "\nmy floateger: " << floateger
            << "\nmy doublager: " << doublager
            << "\nmy longeger: " << longeger;
        dt.EndTimer();
        dt.ElapsedInNanoSeconds();
        dt.StoreTime();
    }
    coutTimeAverage = dt.Average();
    coutTimeMin = dt.TimeMin();
    coutTimeMax = dt.TimeMax();

}

void usePrintF()
{
    timer_average dt2;
    for (int i = 0; i < NUM_LOOPS; i++)
    {
        dt2.StartTimer();
        std::printf("\n\nI am using Print F right now. I like numbers.\nmy integer: %i\nmy floateger: %f\nmy doublager: %lf\nmy longeger: %li", integer, floateger, doublager, longeger);
        dt2.EndTimer();
        dt2.ElapsedInNanoSeconds();
        dt2.StoreTime();
    }
    printFTimeAverage = dt2.Average();
    printFTimeMin = dt2.TimeMin();
    printFTimeMax = dt2.TimeMax();
}

int main()
{
    std::cout << "Hello World!\n";
    useCOut();
    usePrintF();

    std::cout << "\n\n\nCout Average: " << coutTimeAverage << "\nCout Min: " << coutTimeMin << "\nCout Max: " << coutTimeMax
        << "\n\nPrintF Average: " << printFTimeAverage << "\nPrintF Min: " << printFTimeMin << "\nPrintF Max: "<< printFTimeMax
        << "\n\n";
}


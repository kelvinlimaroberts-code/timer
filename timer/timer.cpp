#include <iostream>
#include "timer.h"
const int NUM_LOOPS = 1000;
int integer = 765;
float floateger = 87346.7635;
double doublager = 173264.821368;
long longeger = 23456789;
long long coutTime = 0;
long long printFTime = 0;

void useCOut()
{
    timer dt;
    dt.StartTimer();
    for (int i = 0; i < NUM_LOOPS; i++)
    {
        std::cout << "\nI am using C Out right now. I like numbers."
            << "\nmy integer: " << integer
            << "\nmy floateger: " << floateger
            << "\nmy doublager: " << doublager
            << "\nmy longeger: " << longeger;
    }
    
    dt.EndTimer();
    coutTime = dt.ElapsedInMicroSeconds();
}

void usePrintF()
{
    timer dt2;
    dt2.StartTimer();
    for (int i = 0; i < NUM_LOOPS; i++)
    {
        std::printf("\n\nI am using Print F right now. I like numbers.\nmy integer: %i\nmy floateger: %f\nmy doublager: %lf\nmy longeger: %li", integer, floateger, doublager, longeger);
    }
    dt2.EndTimer();
    printFTime = dt2.ElapsedInMicroSeconds();
}

int main()
{
    std::cout << "Hello World!\n";
    useCOut();
    usePrintF();

    std::cout << "\n\nCout Time: " << coutTime << "\nPrintF Time: " << printFTime;
}


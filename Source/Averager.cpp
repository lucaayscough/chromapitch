#include "Headers.h"


Averager::Averager() {}

Averager::~Averager() {}

void Averager::add(double valueToAdd)
{
    ++valueCount;
    valueSum += valueToAdd;
}

double Averager::getAverage()
{
    auto outputSum = valueSum / static_cast<double> (valueCount);
    
    valueCount = 0;
    valueSum = 0.0;
    
    return outputSum;
}

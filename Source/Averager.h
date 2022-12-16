#pragma once


class Averager
{
public:
    Averager();
    ~Averager();

    void add(double valueToAdd);
    double getAverage();
    
private:
    int valueCount = 0;
    double valueSum = 0.0;
};

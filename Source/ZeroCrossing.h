#pragma once


class ZeroCrossing
{
public:
    ZeroCrossing();
    ~ZeroCrossing();
    
    double getFrequency();
    bool isReadingValid();
    void prepareToPlay(double sampleRate);
    void computeFrequency(juce::AudioBuffer<float>& buffer);
    
private:
    int numCrossings = 0;
    double window = 0;
    bool sign = false;
    double sampleRate;
    
    double currentSample = 0.0;
    double previousSample = 0.0;
    
    double frequency = 0.0;
    bool validReading = false;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroCrossing)
};

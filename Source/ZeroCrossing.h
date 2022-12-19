#pragma once


class ZeroCrossing
{
public:
    ZeroCrossing();
    ~ZeroCrossing();
    
    void prepareToPlay(double sampleRate);
    void getFrequency(juce::AudioBuffer<float>& buffer);
    
private:
    int numCrossings = 0;
    double window = 0;
    bool sign = false;
    double sampleRate;
    
    double currentSample = 0.0;
    double previousSample = 0.0;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroCrossing)
};

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
    bool sign = true;
    double sampleRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ZeroCrossing)
};

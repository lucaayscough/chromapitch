#pragma once


class YIN
{
public:
    YIN();
    ~YIN();
    
    void setSampleRate(double sampleRate);
    void setWindowSize(double windowSize);
    
    void prapareToPlay(double sampleRate, double windowSize);
    
    double autoCorrelate(int step, int lag);
    double difference(int step, int lag);
    void detectFrequency(juce::AudioBuffer<float>& buffer);
    
private:
    juce::Array<float> m_buffer;
    double m_sampleRate = 48000;
    double m_frequency = 0;
    int m_windowSize = 512;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YIN)
};

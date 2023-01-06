#pragma once


class YIN
{
public:
    YIN();
    ~YIN();
    
    void setSampleRate(float sampleRate);
    void setWindowSize(float windowSize);
    
    void prapareToPlay(float sampleRate, float windowSize);
    
    void difference();
    void cumulativeMeanNormalizedDifference();
    int absoluteThreshold();
    float detectFrequency();
    void processBlock(juce::AudioBuffer<float>& buffer);
    

private:
    int m_bufferSize = 512;
    int m_windowSize = 512;
    float m_threshold = 0.1;
    float m_probablity = 0;
    float m_sampleRate = 48000;

    juce::Array<float> m_buffer;
    juce::Array<float> m_yinBuffer;
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YIN)
};

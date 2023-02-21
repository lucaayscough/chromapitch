#pragma once


class YIN
{
public:
    YIN();
    ~YIN();
    
    void setSampleRate(float sampleRate);
    void setWindowSize(float windowSize);
    void setFrequency(float frequency);
    
    float getNextFrequency();

    void prapareToPlay(float sampleRate, float windowSize);
    void processBlock(juce::AudioBuffer<float>& buffer);

    void reset();

private:
    void difference();
    void cumulativeMeanNormalizedDifference();
    int absoluteThreshold();
    float parabolicInterpolation(int tauEstimate);
    void detectFrequency();

private:
    bool m_isReset = true;
    int m_bufferSize = 512;
    int m_windowSize = 512;
    float m_threshold = 0.1;
    float m_sampleRate = 48000;
    float m_frequency = -1;

    juce::Array<float> m_buffer;
    juce::Array<float> m_yinBuffer;
     
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(YIN)
};

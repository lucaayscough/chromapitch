#include "Headers.h"


YIN::YIN() {}

YIN::~YIN() {}

void YIN::setSampleRate(double sampleRate)
{
    m_sampleRate = sampleRate;
}

void YIN::setWindowSize(double windowSize)
{
    m_windowSize = windowSize;
}

void YIN::prapareToPlay(double sampleRate, double windowSize)
{
    setSampleRate(sampleRate);
    setWindowSize(windowSize);
}

double YIN::autoCorrelate(int step, int lag)
{
    double sum = 0;
    
    for (int i = 0; i < m_windowSize; ++i)
    {
        sum += m_buffer[i + step] * m_buffer[i + step + lag + m_windowSize];
    }
    
    return sum;
}

double YIN::difference(int step, int lag)
{
    return autoCorrelate(step, 0) + autoCorrelate(step, lag) - (2 * autoCorrelate(step, lag));
}

void YIN::detectFrequency(juce::AudioBuffer<float>& buffer)
{
    // Fill internal buffer with samples.
    auto* channelData = buffer.getWritePointer(0);
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        m_buffer.add(channelData[i]);
    }
    
    if (m_buffer.size() >= m_windowSize * 2)
    {
        auto val = difference(0, 10);
        DBG (val);
        
        m_buffer.removeRange(0, m_windowSize);
    }

    
}

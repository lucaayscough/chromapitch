#include "Headers.h"


YIN::YIN() {}

YIN::~YIN() {}

void YIN::setSampleRate(float sampleRate)
{
    m_sampleRate = sampleRate;
}

void YIN::setWindowSize(float windowSize)
{
    m_windowSize = windowSize;
    m_bufferSize = windowSize * 2;

    m_buffer.clear();
    m_buffer.ensureStorageAllocated(m_bufferSize);
}

void YIN::prapareToPlay(float sampleRate, float windowSize)
{
    setSampleRate(sampleRate);
    setWindowSize(windowSize);

    m_yinBuffer.clear();
    m_yinBuffer.ensureStorageAllocated(m_bufferSize);


    m_buffer.clear();
    m_buffer.ensureStorageAllocated(m_bufferSize);
}

void YIN::difference()
{
    float delta;

    for (int tau = 0; tau < m_windowSize; ++tau)
    {
        for (int i = 0; i < m_windowSize; ++i)
        {
            delta = m_buffer[i] - m_buffer[i + tau];
            m_yinBuffer.set(tau, m_yinBuffer[tau] + (delta * delta));
        }
    }
}

void YIN::cumulativeMeanNormalizedDifference()
{
    float runningSum = 0;
    m_yinBuffer.set(0, 1);

    for (int tau = 1; tau < m_windowSize; ++tau)
    {
        runningSum += m_yinBuffer[tau]; 
        m_yinBuffer.set(tau, m_yinBuffer[tau] * tau / runningSum);
    }
}

int YIN::absoluteThreshold()
{
   int tau;

   for (tau = 2; tau < m_windowSize; ++tau)
   {
        if (m_yinBuffer[tau] < m_threshold)
        {
            while (tau + 1 < m_windowSize && m_yinBuffer[tau + 1] < m_yinBuffer[tau])
            {
                ++tau;
            } 
            
            break;
        }
   }

   if (tau == m_windowSize || m_yinBuffer[tau + 1] >= m_threshold)
   {
        tau = -1;
   }

   return tau;
}

float YIN::detectFrequency()
{
    difference();
    cumulativeMeanNormalizedDifference();
    auto tau = absoluteThreshold(); 
    
    if (tau == -1)
    {
        return -1;
    }

    return m_sampleRate / tau; 
}

void YIN::processBlock(juce::AudioBuffer<float>& signal)
{
    auto* channelData = signal.getWritePointer(0);
    
    // Fill buffer with incoming audio data.
    for (int i = 0; i < signal.getNumSamples(); ++i)
    {
        m_buffer.add(channelData[i]);
    }

    // Detect frequency if buffer has collected enough samples.
    if (m_buffer.size() >= m_bufferSize)
    {
        int numRuns = (m_buffer.size() / m_windowSize) - 1; 
        
        for (int i = 0; i < numRuns; ++i)
        {
            auto frequency = detectFrequency();
            DBG(frequency);
            
            // Prepare for next run.
            m_yinBuffer.clearQuick(); 
            m_buffer.removeRange(0, m_windowSize);
        }
    }
}


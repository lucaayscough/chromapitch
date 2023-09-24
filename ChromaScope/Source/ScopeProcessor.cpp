#include "Headers.h"


ScopeProcessor::ScopeProcessor() : m_ringBuffer (m_bufferSize) {}

ScopeProcessor::~ScopeProcessor() {}

void ScopeProcessor::prepareToPlay (float _sampleRate) 
{
    m_sampleRate = _sampleRate;
    m_numSamples = m_sampleRate / m_captureRateHz;
}

void ScopeProcessor::processBlock (juce::AudioBuffer<float> _buffer)
{
    if (_buffer.getNumChannels() < 2)
    {
        throw std::runtime_error("Channel configuration needs to be stereo.");
    }

    for (int i = 0; i < _buffer.getNumSamples(); ++i)
    {
        if (m_head == 0)
        {
            auto* ch1 = _buffer.getReadPointer (0);
            auto* ch2 = _buffer.getReadPointer (1);

            Chroma::Point point;      
            point.x = ch1[i];
            point.y = ch2[i];
            
            m_ringBuffer.push (point);
        }
        
        m_head = (m_head + 1) % m_numSamples;
    }
}

Chroma::RingBuffer<Chroma::Point>& ScopeProcessor::getRingBuffer()
{
    return m_ringBuffer;
}

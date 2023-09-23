#include "Headers.h"


ScopeProcessor::ScopeProcessor() : m_ringBuffer (512)
{
}

ScopeProcessor::~ScopeProcessor() {}

void ScopeProcessor::prepareToPlay (float _sampleRate) 
{
    m_sampleRate = _sampleRate;
    m_numSamples = m_sampleRate / m_scopeRate;
}

void ScopeProcessor::processBlock (juce::AudioBuffer<float> _buffer)
{
    auto* ch1 = _buffer.getWritePointer (0);
    auto* ch2 = _buffer.getWritePointer (1);

    Chroma::Point point;      
    point.x = ch1[0];
    point.y = ch2[0];
    
    m_ringBuffer.push (point);
}

Chroma::RingBuffer<Chroma::Point>& ScopeProcessor::getRingBuffer()
{
    return m_ringBuffer;
}

#include "Headers.h"


ScopeProcessor::ScopeProcessor() : m_ringBuffer (512)
{

}

ScopeProcessor::~ScopeProcessor() {}

void ScopeProcessor::prepareToPlay (float _sampleRate) 
{
    m_sampleRate = _sampleRate;
}

void ScopeProcessor::processBlock (juce::AudioBuffer<float> _buffer)
{
    // processing
}

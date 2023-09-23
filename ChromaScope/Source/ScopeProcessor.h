#pragma once


class ScopeProcessor
{
public:
    ScopeProcessor();
    ~ScopeProcessor();

    void prepareToPlay (float _sampleRate);
    void processBlock (juce::AudioBuffer<float> _buffer);

private:
    float m_sampleRate = 0.f;
    Chroma::RingBuffer<float> m_ringBuffer;
};

#pragma once


class ScopeProcessor
{
public:
    ScopeProcessor();
    ~ScopeProcessor();

    void prepareToPlay (float _sampleRate);
    void processBlock (juce::AudioBuffer<float> _buffer);

    Chroma::RingBuffer<Chroma::Point>& getRingBuffer();

private:
    float m_sampleRate = 0.f;
    int m_scopeRate = 60;
    int m_numSamples;
    int m_head = 0;
    Chroma::RingBuffer<Chroma::Point> m_ringBuffer;
};

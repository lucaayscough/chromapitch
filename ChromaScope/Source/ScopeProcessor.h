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
    int m_captureRateHz = 120;
    int m_numSamples;
    int m_head = 0;
    const std::size_t m_bufferSize = 1024;
    Chroma::RingBuffer<Chroma::Point> m_ringBuffer;
};

#pragma once


struct AudioContainer{
    AudioContainer();
    ~AudioContainer();

    static const int M_NUM_SAMPLES;
    static const int M_NUM_CHANNELS;

    juce::OwnedArray<juce::AudioBuffer<float>> m_AudioBuffers; 

    juce::Array<float> m_Audio;
    bool m_PlayAudio;
    juce::Array<int> m_SampleIndex;
};
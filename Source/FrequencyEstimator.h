#pragma once


class FrequencyEstimator
{
public:
    FrequencyEstimator();
    ~FrequencyEstimator();

    Chroma::NoteInfo getLastNote();

    void prepareToPlay(double sampleRate, float lowestFrequency, float highestFrequency);
    void processBlock(juce::AudioBuffer<float>& buffer);
    
private:
    std::shared_ptr<cycfi::q::pitch_detector> m_bacf;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyEstimator)
};

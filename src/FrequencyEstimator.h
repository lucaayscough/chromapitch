#pragma once


class FrequencyEstimator
{
public:
    FrequencyEstimator();
    ~FrequencyEstimator();

    chroma::NoteInfo& getLastNote();

    void preprocess(juce::AudioBuffer<float>& buffer);
    void prepareToPlay(double sampleRate, float lowestFrequency, float highestFrequency);
    void processBlock(juce::AudioBuffer<float>& buffer);
    
private:
    float getFrequency();
    void updateFrequency(float frequency);
    void updateNote();

private:
    std::shared_ptr<cycfi::q::pitch_detector> m_bacf;
    std::shared_ptr<cycfi::q::pitch_detector> m_bacf2;
    chroma::NoteInfo m_note;
    std::atomic<float> m_frequency;

    juce::OwnedArray<juce::IIRFilter> m_filters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyEstimator)
};

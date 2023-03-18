#pragma once


class FrequencyEstimator
{
public:
    FrequencyEstimator();
    ~FrequencyEstimator();

    chroma::NoteInfo& getLastNote();

    void prepareToPlay(double sampleRate, float lowestFrequency, float highestFrequency);
    void processBlock(juce::AudioBuffer<float>& buffer);
    
private:
    float getFrequency();
    void updateFrequency();
    void updateNote();

private:
    std::shared_ptr<cycfi::q::pitch_detector> m_bacf;
    chroma::NoteInfo m_note;
    std::atomic<float> m_frequency;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FrequencyEstimator)
};

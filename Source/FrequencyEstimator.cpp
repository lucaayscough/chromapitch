#include "Headers.h"


FrequencyEstimator::FrequencyEstimator() {}
FrequencyEstimator::~FrequencyEstimator() {}

Chroma::NoteInfo FrequencyEstimator::getLastNote()
{
    Chroma::NoteInfo note;
    note.frequency = m_bacf->get_frequency();

    return note;
}

void FrequencyEstimator::prepareToPlay(double sampleRate, float lowestFrequency, float highestFrequency)
{
    cycfi::q::frequency lowest_freq(lowestFrequency);
    cycfi::q::frequency highest_freq(highestFrequency);
    cycfi::q::decibel hysteresis(0);
    
    m_bacf = std::make_shared<cycfi::q::pitch_detector>(lowest_freq, highest_freq, sampleRate, hysteresis);
}

void FrequencyEstimator::processBlock(juce::AudioBuffer<float>& buffer)
{
    if (buffer.getRMSLevel(0, 0, buffer.getNumSamples()) < Variables::rmsThreshold)
    {
        m_bacf->reset();
        return;
    }
    
    auto* channelData = buffer.getWritePointer(0);
    
    auto& pd = *m_bacf;
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        pd(channelData[i]);
    }
}

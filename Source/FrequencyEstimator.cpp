#include "Headers.h"


FrequencyEstimator::FrequencyEstimator() {}
FrequencyEstimator::~FrequencyEstimator() {}

chroma::NoteInfo& FrequencyEstimator::getLastNote()
{
    updateNote();
    return m_note;
}

void FrequencyEstimator::prepareToPlay(double sampleRate, float lowestFrequency, float highestFrequency)
{
    cycfi::q::frequency lowest_freq(lowestFrequency);
    cycfi::q::frequency highest_freq(highestFrequency);
    cycfi::q::decibel hysteresis(0);
    
    m_bacf = std::make_shared<cycfi::q::pitch_detector>(lowest_freq, highest_freq, sampleRate, hysteresis);
    m_bacf2 = std::make_shared<cycfi::q::pitch_detector>(lowest_freq, highest_freq, sampleRate, hysteresis);
}

void FrequencyEstimator::processBlock(juce::AudioBuffer<float>& buffer)
{
    if (buffer.getRMSLevel(0, 0, buffer.getNumSamples()) < Variables::rmsThreshold)
    {
        m_bacf->reset();
        m_bacf2->reset();
        updateFrequency(-1);
        return;
    }
   
    auto* channelData = buffer.getWritePointer(0);
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        auto isReady = (*m_bacf)(channelData[i]);
        auto isReady2 = (*m_bacf2)(channelData[i]);

        if (isReady && isReady2)
        {
            if (m_bacf->periodicity() > 0.8 && m_bacf2->periodicity() > 0.8)
            {
                updateFrequency((m_bacf->get_frequency() + m_bacf2->get_frequency()) * 0.5);
            }

            else
            {
                m_bacf->reset();
                m_bacf2->reset();
                updateFrequency(-1);
            }
        }

        else
        {
            updateFrequency((m_bacf->predict_frequency() + m_bacf2->predict_frequency()) * 0.5);
        }
    }
}

float FrequencyEstimator::getFrequency()
{
    return m_frequency.load();
}

void FrequencyEstimator::updateFrequency(float frequency)
{
    m_frequency = frequency;
    
    if (m_frequency == 0.f)
    {
        m_frequency = -1;
    }
}

void FrequencyEstimator::updateNote()
{
    auto frequency = getFrequency();

    if (m_note.frequency != frequency)
    {
        m_note.frequency = frequency;
        m_note.note = chroma::Midi::frequencyToMidi(frequency);
        m_note.cents = chroma::Midi::centsFromNearestNote(frequency); 
    }

    else if (frequency == -1)
    {
        m_note.frequency = -1;
        m_note.note = -1;
        m_note.cents = -1;
    }
}


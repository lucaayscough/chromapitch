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
    cycfi::q::decibel hysteresis = cycfi::q::lin_to_db(0);
    
    m_bacf = std::make_shared<cycfi::q::pitch_detector>(lowest_freq, highest_freq, sampleRate, hysteresis);
    m_bacf2 = std::make_shared<cycfi::q::pitch_detector>(lowest_freq, highest_freq, sampleRate, hysteresis);

    m_filters.clear();
    
    for (int filter = 0; filter < Variables::numFilters; ++filter)
    {
        m_filters.add (new juce::IIRFilter);
        m_filters[filter]->reset();

        if (filter < Variables::numFilters / 2)
        {
            m_filters[filter]->setCoefficients(juce::IIRCoefficients::makeHighPass(sampleRate, lowestFrequency));
        }

        else
        {
            m_filters[filter]->setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, highestFrequency));
        }
    }
}

void FrequencyEstimator::preprocess(juce::AudioBuffer<float>& buffer)
{
    auto* channelData = buffer.getWritePointer(0);
    
    for (int filter = 0; filter < Variables::numFilters; ++filter)
    {
        m_filters[filter]->processSamples(channelData, buffer.getNumSamples());   
    }
}

void FrequencyEstimator::processBlock(juce::AudioBuffer<float>& buffer)
{
    preprocess(buffer);

    if (buffer.getRMSLevel(0, 0, buffer.getNumSamples()) < Variables::rmsThreshold)
    {
        m_bacf->reset();
        updateFrequency(-1);
        return;
    }
   
    auto* channelData = buffer.getWritePointer(0);
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        auto isReady = (*m_bacf)(channelData[i]);
        auto frequency = m_bacf->predict_frequency();

        if (isReady)
        {
            if (m_bacf->periodicity() > 0.9)
            {
                frequency = m_bacf->get_frequency();
            }

            else
            {
                frequency = -1;
            }
        }

        updateFrequency(frequency);
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


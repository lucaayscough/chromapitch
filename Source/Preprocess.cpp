#include "Headers.h"


Preprocess::Preprocess() {}

Preprocess::~Preprocess() {}

void Preprocess::prepareToPlay(double sampleRate)
{
    m_sampleRate = sampleRate;

    m_lowpassFilter_1.setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, Variables::maximumFrequency));
    m_lowpassFilter_2.setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, Variables::maximumFrequency));
    m_lowpassFilter_3.setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, Variables::maximumFrequency));
    m_lowpassFilter_4.setCoefficients(juce::IIRCoefficients::makeLowPass(sampleRate, Variables::maximumFrequency));

    m_highpassFilter_1.setCoefficients(juce::IIRCoefficients::makeHighPass(sampleRate, Variables::minimumFrequency)); 
    m_highpassFilter_2.setCoefficients(juce::IIRCoefficients::makeHighPass(sampleRate, Variables::minimumFrequency));
    m_highpassFilter_3.setCoefficients(juce::IIRCoefficients::makeHighPass(sampleRate, Variables::minimumFrequency));
    m_highpassFilter_4.setCoefficients(juce::IIRCoefficients::makeHighPass(sampleRate, Variables::minimumFrequency));
}

void Preprocess::processBlock(juce::AudioBuffer<float>& buffer)
{
    // take buffer and convert to mono by averaging the left and right channels
    if (buffer.getNumChannels() == 2)
    {
        buffer.setSize(1, buffer.getNumSamples(), true, false);
    }

    // filter the audio to remove some of the noise
    m_lowpassFilter_1.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
    m_lowpassFilter_2.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
    m_lowpassFilter_3.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
    m_lowpassFilter_4.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
    
    m_highpassFilter_1.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
    m_highpassFilter_2.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
    m_highpassFilter_3.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
    m_highpassFilter_4.processSamples(buffer.getWritePointer(0), buffer.getNumSamples());
}

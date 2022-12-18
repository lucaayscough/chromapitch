#include "Headers.h"


//================================================//
// Base oscillator class.

Oscillator::Oscillator() {}

Oscillator::~Oscillator() {}

void Oscillator::setFrequency(float frequencyToUse)                 { frequency = frequencyToUse; }
void Oscillator::setSampleRate(float sampleRateToUse)               { sampleRate = sampleRateToUse; }
void Oscillator::setPhase(float phaseToUse)                         { phase = phaseToUse; }
void Oscillator::setPhaseDelta(float phaseDeltaToUse)               { phaseDelta = phaseDeltaToUse; }

float Oscillator::getFrequency()                                    { return frequency; }
float Oscillator::getSampleRate()                                   { return sampleRate; }
float Oscillator::getPhase()                                        { return phase; }
float Oscillator::getPhaseDelta()                                   { return phaseDelta; }

void Oscillator::updatePhase()
{
    phase += phaseDelta;
    
    if(phase > 1.0f)
        phase -= 1.0f;
}

void Oscillator::updatePhaseDelta()
{
    phaseDelta = frequency / sampleRate;
}

void Oscillator::prepareToPlay(float sampleRateToUse)
{
    setSampleRate(sampleRateToUse);
}

void Oscillator::prepareToPlay(float frequencyToUse, float sampleRateToUse)
{
    setFrequency(frequencyToUse);
    setSampleRate(sampleRateToUse);
}

float Oscillator::output()
{
    return getPhase();
}

float Oscillator::processSample()
{
    updatePhaseDelta();
    
    float sample = output();
    updatePhase();
    
    return sample;
}

void Oscillator::processBlock(juce::AudioBuffer<float>& buffer)
{
    updatePhaseDelta();
    
    const auto numChannels = buffer.getNumChannels();
    const auto numSamples = buffer.getNumSamples();

    float samples[numSamples];
    
    for (int sample = 0; sample < numSamples; ++sample)
    {
        samples[sample] = output();
        updatePhase();
    }
    
    for (int channel = 0; channel < numChannels; ++channel)
    {
        auto* bufferData = buffer.getWritePointer(channel);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            bufferData[sample] = samples[sample];
        }
    }
}


//================================================//
// Sine wave oscillator.

SineOscillator::SineOscillator() {}

float SineOscillator::output()
{
    return std::sin(2.0f * getPhase() * M_PI);
}


//================================================//
// Square wave oscillator.

SquareOscillator::SquareOscillator() {}

void SquareOscillator::setPulseWidth(float pulseWidthToUse)          { pulseWidth = pulseWidthToUse; }

float SquareOscillator::getPulseWidth()                              { return pulseWidth; }

float SquareOscillator::output()
{
    if (getPhase() < pulseWidth)
    {
        return 1.0f;
    }
    
    else
    {
        return -1.0f;
    }
}


//================================================//
// Triangle wave oscillator.

TriangleOscillator::TriangleOscillator() {}

float TriangleOscillator::output()
{
    // Algorithm used to compute triangle wave in range [-1,1] --> https://wikimedia.org/api/rest_v1/media/math/render/svg/bc9fd743afd5943b7f83248e59d55d97119257b9
    return 2.0f * std::fabs(2.0f * (getPhase() - std::floor(getPhase() + 0.5f))) - 1.0f;
}


//================================================//
// Sawtooth wave oscillator.

SawtoothOscillator::SawtoothOscillator() {}

float SawtoothOscillator::output()
{
    // Algorithm used to compute sawtooth wave in range [-1,1] --> https://wikimedia.org/api/rest_v1/media/math/render/svg/0f07cb8c8f5850b17ad8c3415800046cd1f38967
    return 2.0f * (getPhase() - std::floor(0.5f + getPhase()));
}

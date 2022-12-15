#include "Headers.h"


//================================================//
// Base oscillator class.

Oscillator::Oscillator() {}

Oscillator::~Oscillator() {}


//================================================//
// Setter methods.

void Oscillator::setFrequency (float frequency)                     { m_Frequency = frequency; }
void Oscillator::setSampleRate (float sampleRate)                   { m_SampleRate = sampleRate; }
void Oscillator::setBlockSize (int blockSize)                       { m_BlockSize = blockSize; }
void Oscillator::setPhase (float phase)                             { m_Phase = phase; }
void Oscillator::setPhaseDelta (float phaseDelta)                   { m_PhaseDelta = phaseDelta; }


//================================================//
// Getter methods.

float Oscillator::getFrequency()                                    { return m_Frequency; }
float Oscillator::getSampleRate()                                   { return m_SampleRate; }
int Oscillator::getBlockSize()                                      { return m_BlockSize; }
float Oscillator::getPhase()                                        { return m_Phase; }
float Oscillator::getPhaseDelta()                                   { return m_PhaseDelta; }
juce::AudioBuffer<float>& Oscillator::getBlock()                    { return m_Buffer; }


//================================================//
// Phase methods.

/**
    Updates the phase of the oscillator's cycle by adding a phase delta value.
 */
void Oscillator::updatePhase()
{
    m_Phase += m_PhaseDelta;
    
    if (m_Phase > 1.0f)
        m_Phase -= 1.0f;
}

/**
    Updates the phase delta of the oscllator based on the current frequency
    and sample rate.
 */
void Oscillator::updatePhaseDelta()
{
    m_PhaseDelta = m_Frequency / m_SampleRate;
}


//================================================//
// Init methods.

/**
    Prepares the oscillator for playback.
    @param frequency Frequency to use.
    @param sampleRate Sample rate to use.
    @param blockSize Block size to use.
 */

void Oscillator::prepareToPlay (float frequency, float sampleRate, int blockSize)
{
    setFrequency (frequency);
    setSampleRate (sampleRate);
    setBlockSize (blockSize);
    
    m_Buffer.setSize(1, blockSize);
    
    updatePhaseDelta();
}


//================================================//
// DSP methods.

/**
    Virtual method that returns the phase to be outputted.
    @param phase Phase to use.
 */

float Oscillator::output (float phase)
{
    return phase;
}

/**
    Processes a single sample, updates the phase of the oscillator and returns the sample.
 */

float Oscillator::processSample()
{
    float sample = output (m_Phase);
    updatePhase();
    
    return sample;
}

/**
    Processes a block of samples and updates the phase of the oscillator.
 */

void Oscillator::processBlock()
{
    m_Buffer.clear();
    auto* bufferData = m_Buffer.getWritePointer (0);
    
    for (int i = 0; i < m_BlockSize; i++)
    {
        bufferData[i] = output (m_Phase);
        updatePhase();
    }
}


//================================================//
// Sine wave oscillator.

SineOscillator::SineOscillator() {}

/**
    Outputs the sample value for the current phase based on sine wave algorithm.
    @param phase Phase to use.
 */

float SineOscillator::output (float phase)
{
    return std::sin(2.0f * phase * M_PI);
}


//================================================//
// Square wave oscillator.

SquareOscillator::SquareOscillator() {}

/**
    Outputs the sample value for the current phase based on square wave algorithm.
    @param phase Phase to use.
 */

float SquareOscillator::output (float phase)
{
    if (phase < 0.5f)
        return 1.0f;
    
    else
        return -1.0f;
}


//================================================//
// Pulse wave oscillator.

PulseOscillator::PulseOscillator() {}


//================================================//                
// Setter methods.

void PulseOscillator::setPulseWidth (float pulseWidth)              { m_PulseWidth = pulseWidth; }


//================================================//
// Getter methods.

float PulseOscillator::getPulseWidth()                              { return m_PulseWidth; }


//================================================//
// DSP methods.

/**
    Outputs the sample value for the current phase based on pulse wave algorithm.
    @param phase Phase to use.
 */

float PulseOscillator::output (float phase)
{
    if (phase < m_PulseWidth)
        return 1.0f;
    
    else
        return -1.0f;
}


//================================================//
// Triangle wave oscillator.

TriangleOscillator::TriangleOscillator() {}


//================================================//
// DSP methods.

/**
    Outputs the sample value for the current phase based on triangle wave algorithm.
    @param phase Phase to use.
 */

float TriangleOscillator::output (float phase)
{
    // Algorithm used to compute triangle wave in range [-1,1] --> https://wikimedia.org/api/rest_v1/media/math/render/svg/bc9fd743afd5943b7f83248e59d55d97119257b9
    return 2.0f * std::fabs(2.0f * (phase - std::floor(phase + 0.5f))) - 1.0f;
}


//================================================//
// Sawtooth wave oscillator.

SawtoothOscillator::SawtoothOscillator() {}


//================================================//
// DSP methods.

/**
    Outputs the sample value for the current phase based on sawtooth wave algorithm.
    @param phase Phase to use.
 */

float SawtoothOscillator::output (float phase)
{
    // Algorithm used to compute sawtooth wave in range [-1,1] --> https://wikimedia.org/api/rest_v1/media/math/render/svg/0f07cb8c8f5850b17ad8c3415800046cd1f38967
    return 2.0f * (phase - std::floor(0.5f + phase));
}

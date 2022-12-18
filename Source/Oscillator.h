#pragma once


//================================================//
/// Base oscillator class which outputs a phasor wave.

class Oscillator
{
public:
    Oscillator();
    virtual ~Oscillator();
    
    // Setter methods.
    void setFrequency(float frequencyToUse);
    void setSampleRate(float sampleRateToUse);
    void setPhase(float phaseToUse);
    void setPhaseDelta(float phaseDeltaToUse);
    
    // Getter methods.
    float getFrequency();
    float getSampleRate();
    float getPhase();
    float getPhaseDelta();
    
    // Phase methods.
    void updatePhase();
    void updatePhaseDelta();
    
    // Init methods.
    void prepareToPlay(float sampleRateToUse);
    void prepareToPlay(float frequencyToUse, float sampleRateToUse);
    
    // DSP methods.
    virtual float output();
    float processSample();
    void processBlock(juce::AudioBuffer<float>& buffer);
    
private:
    float frequency = 0.f;
    float sampleRate = 0.f;
    float phase = 0.f;
    float phaseDelta = 0.f;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Oscillator)
};


//================================================//
/// Square wave oscillator class.

class SineOscillator : public Oscillator
{
public:
    SineOscillator();
    
    // DSP methods.
    float output() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineOscillator)
};


//================================================//
/// Square wave oscillator class.

class SquareOscillator : public Oscillator
{
public:
    SquareOscillator();
    
    // Setter methods.
    void setPulseWidth(float pulseWidthToUse);
    
    // Getter methods.
    float getPulseWidth();
    
    // DSP methods.
    float output() override;
    
private:
    float pulseWidth = 0.5f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SquareOscillator)
};


//================================================//
/// Triangle wave oscillator class.

class TriangleOscillator : public Oscillator
{
public:
    TriangleOscillator();
    
    // DSP methods.
    float output() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TriangleOscillator)
};


//================================================//
/// Sawtooth wave oscillator class.

class SawtoothOscillator : public Oscillator
{
public:
    SawtoothOscillator();
    
    // DSP methods.
    float output() override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SawtoothOscillator)
};

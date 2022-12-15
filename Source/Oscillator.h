#pragma once


//================================================//
/// Base oscillator class which outputs a phasor wave.

class Oscillator
{
public:
    Oscillator();
    virtual ~Oscillator();
    
    // Setter methods.
    void setFrequency (float frequency);
    void setSampleRate (float sampleRate);
    void setBlockSize (int blockSize);
    void setPhase (float phase);
    void setPhaseDelta (float phaseDelta);
    
    // Getter methods.
    float getFrequency();
    float getSampleRate();
    int getBlockSize();
    float getPhase();
    float getPhaseDelta();
    juce::AudioBuffer<float>& getBlock();
    
    // Phase methods.
    void updatePhase();
    void updatePhaseDelta();
    
    // Init methods.
    void prepareToPlay (float frequency, float sampleRate, int blockSize);
    
    // DSP methods.
    virtual float output (float phase);
    float processSample();
    void processBlock();
    
private:
    float m_Frequency;
    float m_SampleRate;
    float m_BlockSize;
    float m_Phase;
    float m_PhaseDelta;
    juce::AudioBuffer<float> m_Buffer;

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
    float output (float phase) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SineOscillator)
};


//================================================//
/// Square wave oscillator class.

class SquareOscillator : public Oscillator
{
public:
    SquareOscillator();
    
    // DSP methods.
    float output (float phase) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SquareOscillator)
};


//================================================//
/// Pulse wave oscillator class.

class PulseOscillator : public Oscillator
{
public:
    PulseOscillator();
    
    // Setter methods.
    void setPulseWidth (float pulseWidth);
    
    // Getter methods.
    float getPulseWidth();
    
    // DSP methods.
    float output (float phase) override;
    
private:
    float m_PulseWidth = 0.5f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PulseOscillator)
};


//================================================//
/// Triangle wave oscillator class.

class TriangleOscillator : public Oscillator
{
public:
    TriangleOscillator();
    
    // DSP methods.
    float output (float phase) override;

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
    float output (float phase) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SawtoothOscillator)
};

#pragma once


class Preprocess
{
public:
    Preprocess();
    ~Preprocess();

    void prepareToPlay(double sampleRate);
    void processBlock(juce::AudioBuffer<float>& buffer);

private:
    juce::IIRFilter m_lowpassFilter_1;   
    juce::IIRFilter m_lowpassFilter_2;   
    juce::IIRFilter m_lowpassFilter_3;   
    juce::IIRFilter m_lowpassFilter_4;   
    
    juce::IIRFilter m_highpassFilter_1;
    juce::IIRFilter m_highpassFilter_2;
    juce::IIRFilter m_highpassFilter_3;
    juce::IIRFilter m_highpassFilter_4;

    double m_sampleRate; 

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Preprocess)
};
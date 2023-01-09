#pragma once


class PitchLine : public juce::Component
{
public:
    PitchLine();
    ~PitchLine();
    
    void update(float frequency);

    void paint(juce::Graphics& g) override;
    void resized() override;

private: 
    juce::Path path;
    juce::OwnedArray<juce::Line<float>> lines;
    juce::Array<float> frequencies;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchLine)
};

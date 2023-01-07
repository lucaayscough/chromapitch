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

    float posX0 = Variables::windowWidth;
    float posX1 = Variables::windowWidth * 2;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchLine)
};

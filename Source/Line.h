#pragma once


class Line : public juce::Component
{
public:
    Line();
    ~Line();
    
    void setFrequency(float frequencyToUse);
    
    bool isFrozen();
    
    void freeze();
    void unfreeze();
    
    void paint(juce::Graphics& g) override;
    void resized() override;
    
    juce::Colour colour = juce::Colours::orange;
    
private:
    juce::Path path;
    
    
    float lineThickness = 5.f;
    float step = 0.f;
    
    bool frozen = true;
    
    float frequency = 0.f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Line)
};

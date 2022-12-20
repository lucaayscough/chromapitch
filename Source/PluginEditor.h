#pragma once


class ChromaPitchAudioProcessorEditor : public juce::AudioProcessorEditor, juce::Timer
{
public:
    ChromaPitchAudioProcessorEditor(ChromaPitchAudioProcessor&);
    ~ChromaPitchAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

private:
    ChromaPitchAudioProcessor& audioProcessor;
    juce::OwnedArray<Line> line;

    float posX0 = 800.f;
    float posX1 = 1600.f;
    
    bool update = true;
    
    int iter = 0;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChromaPitchAudioProcessorEditor)
};

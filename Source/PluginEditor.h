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

    View m_view;
    PitchLine m_pitchLine;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChromaPitchAudioProcessorEditor)
};

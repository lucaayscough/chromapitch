#pragma once


class ChromaPitchAudioProcessorEditor : public juce::AudioProcessorEditor, juce::Timer
{
public:
    ChromaPitchAudioProcessorEditor(ChromaPitchAudioProcessor&);
    ~ChromaPitchAudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

    void mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel) override; 
    void updateBounds();
    
private:
    ChromaPitchAudioProcessor& audioProcessor;

    View m_view;
    PitchLine m_pitchLine;

    float m_scrollPosY = -(Variables::numBoxes * Variables::noteBoxHeight / 2);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChromaPitchAudioProcessorEditor)
};

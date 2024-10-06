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
    void mouseMagnify(const juce::MouseEvent& event, float scaleFactor) override;
    
    void updateBounds();
    
private:
    ChromaPitchAudioProcessor& audioProcessor;

    Header m_header;
    View m_view;
    PitchLine m_pitchLine;

    float m_noteBoxHeight = Variables::noteBoxHeight;
    float m_scrollPosY = -(Variables::numBoxes * m_noteBoxHeight / 2.0f);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChromaPitchAudioProcessorEditor)
};

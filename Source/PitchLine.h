#pragma once


class PitchLine : public juce::Component
{
public:
    PitchLine();
    ~PitchLine();
    
    float getCurrentY();
    void update(Chroma::NoteInfo& note);

    void paint(juce::Graphics& g) override;
    void resized() override;

private: 
    juce::Path m_path;
    juce::Array<int> m_posY; 
    juce::ColourGradient m_gradient;
    Chroma::NoteInfo m_note;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PitchLine)
};

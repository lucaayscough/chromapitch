#pragma once


class View : public juce::Component
{
public:
    View();
    ~View();
    
    void update(chroma::NoteInfo& note);
    void paint(juce::Graphics& g) override;
    void resized() override; 

private:
    juce::OwnedArray<NoteBox> m_noteBoxes;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(View)
};

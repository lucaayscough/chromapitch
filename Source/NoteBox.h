#pragma once


class NoteBox : public juce::Component
{
public:
    NoteBox();
    ~NoteBox();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoteBox)
};

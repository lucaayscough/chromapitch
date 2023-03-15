#pragma once


class MPE
{
public:
    MPE();
    ~MPE();
    
    void processBlock(juce::MidiBuffer& midiMessages, Chroma::NoteInfo& note);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MPE)
};

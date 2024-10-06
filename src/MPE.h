#pragma once


class MPE
{
public:
    MPE();
    ~MPE();
    
    void processBlock(juce::MidiBuffer& midiMessages, chroma::NoteInfo& note);

private:
    bool m_isMPEInit = false;
    bool m_isNoteOn = false; 
    chroma::NoteInfo m_lastNote;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MPE)
};

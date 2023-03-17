#include "Headers.h"


MPE::MPE() {}

MPE::~MPE() {}

void MPE::processBlock(juce::MidiBuffer& midiMessages, Chroma::NoteInfo& note)
{
    midiMessages.clear();

    if (!m_isMPEInit)
    {
        m_isMPEInit = true;
        juce::MPEZoneLayout layout;
        layout.setLowerZone(2, 48, 2);
        auto mpeBuffer = juce::MPEMessages::setZoneLayout(layout);
        midiMessages.swapWith(mpeBuffer);
    }

    if (note.frequency != -1 && m_isNoteOn == false)
    {
        m_isNoteOn = true;
        m_lastNote = note;

        auto pitchBend = Chroma::Midi::getPitchBendMessage(m_lastNote, note);            
        auto noteOn = Chroma::Midi::getNoteOnMessage(note); 

        midiMessages.addEvent(pitchBend, 0);
        midiMessages.addEvent(noteOn, 0);
    }
    
    else if (note.frequency == -1 && m_isNoteOn == true)
    {
        m_isNoteOn = false;
        auto noteOff = Chroma::Midi::getNoteOffMessage(m_lastNote); 
        midiMessages.addEvent(noteOff, 0);
    }

    else if (m_isNoteOn)
    {
        auto pitchBend = Chroma::Midi::getPitchBendMessage(m_lastNote, note);    
        
        pitchBend.setChannel(2);
        midiMessages.addEvent(pitchBend, 0);
    }
}

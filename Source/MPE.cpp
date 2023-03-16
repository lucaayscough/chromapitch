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

    if (Variables::outputMidi)
    {
        if (note.frequency != -1 && m_isNoteOn == false)
        {
            m_isNoteOn = true;
            m_lastNote = note;

            auto pitchBendVal = Chroma::Midi::getPitchBend(Chroma::Midi::distanceInCents(m_lastNote, note));
            
            int msb = (pitchBendVal >> 7) & 0x7F; // extract the most significant 7 bits
            int lsb = pitchBendVal & 0x7F; // extract the least significant 7 bits

            juce::MidiMessage pitchBend(0xE0, lsb, msb);
            juce::MidiMessage noteOn(0x90, note.note, 100);

            pitchBend.setChannel(2);
            noteOn.setChannel(2);
            
            midiMessages.addEvent(pitchBend, 0);
            midiMessages.addEvent(noteOn, 0);
        }
        
        else if (note.frequency == -1 && m_isNoteOn == true)
        {
            m_isNoteOn = false;
            juce::MidiMessage noteOff(0x80, m_lastNote.note, 100);
            noteOff.setChannel(2);
            midiMessages.addEvent(noteOff, 0);
        }

        else if (m_isNoteOn)
        {
            auto pitchBendVal = Chroma::Midi::getPitchBend(Chroma::Midi::distanceInCents(m_lastNote, note));
            
            int msb = (pitchBendVal >> 7) & 0x7F; // extract the most significant 7 bits
            int lsb = pitchBendVal & 0x7F; // extract the least significant 7 bits

            juce::MidiMessage pitchBend(0xE0, lsb, msb);
            pitchBend.setChannel(2);
            midiMessages.addEvent(pitchBend, 0);
        }
    }
}

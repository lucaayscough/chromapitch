#include "Headers.h"


MPE::MPE() {}
MPE::~MPE() {}

void MPE::processBlock(juce::MidiBuffer& midiMessages, Chroma::NoteInfo& note)
{
    midiMessages.clear();

    /*
    // Midi output.
    if (Variables::outputMidi)
    {
        if (lastNote.frequency != -1)
        {
            int note = Chroma::Midi::frequencyToMidi(lastNote.frequency);
        
            if (note != m_lastNote.note)
            {
                juce::MidiMessage noteOff(0x80, m_lastNote.note, 100);
                juce::MidiMessage noteOn(0x90, note, 100);

                m_lastNote = note;

                midiMessages.addEvent(noteOn, 0);
                midiMessages.addEvent(noteOff, 0);
            }
        }
        
        else
        {
            juce::MidiMessage noteOff(0x80, m_lastNote, 100);
            midiMessages.addEvent(noteOff, 0);
        }
    }
    */
}

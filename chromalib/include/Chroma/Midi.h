#pragma once

#include <JuceHeader.h>


namespace chroma
{
    struct NoteInfo
    {
        float frequency = -1;
        int note = -1;
        int cents = -1;
    };

    class Midi
    {   
    public:
        static double frequencyToEqualTemperament(const double frequency)
        {
            return std::log2(frequency / 440.0);
        }

        static int octavesFromA4(const double frequency) 
        {
            return std::round(frequencyToEqualTemperament(frequency));
        }
        
        static int semitonesFromA4(const double frequency)
        {
            return std::round(12 * frequencyToEqualTemperament(frequency));
        }

        static int centsFromA4(const double frequency)
        {
            return std::round(1200 * frequencyToEqualTemperament(frequency)); 
        }

        static int frequencyToMidi(const double frequency)
        {
            return semitonesFromA4(frequency) + 69; 
        }
        
        static int centsFromNearestNote(const double frequency)
        {
            return centsFromA4(frequency) - 100 * semitonesFromA4(frequency); 
        }

        static int distanceInCents(chroma::NoteInfo& note_a, chroma::NoteInfo& note_b)
        {
            auto a = (note_a.note * 100) + note_a.cents;
            auto b = (note_b.note * 100) + note_b.cents;

            return b - a;
        }

        static int getPitchBend(int distanceInCents)
        {
            return 8192 + (static_cast<double> (distanceInCents) * 1.70666666);
        }

        static juce::MidiMessage getNoteOnMessage(chroma::NoteInfo& note)
        {
            juce::MidiMessage noteOn(0x91, note.note, 100);

            return noteOn;
        }

        static juce::MidiMessage getNoteOffMessage(chroma::NoteInfo& note)
        {
            juce::MidiMessage noteOff(0x81, note.note, 100);

            return noteOff;
        }            

        static juce::MidiMessage getPitchBendMessage(chroma::NoteInfo& note_a, chroma::NoteInfo& note_b)
        {
            auto pitchBendVal = chroma::Midi::getPitchBend(chroma::Midi::distanceInCents(note_a, note_b));
            
            int msb = (pitchBendVal >> 7) & 0x7F;
            int lsb = pitchBendVal & 0x7F;

            juce::MidiMessage pitchBend(0xE1, lsb, msb);

            return pitchBend;
        }

        static void printMidiBuffer(juce::MidiBuffer& buffer)
        {
            for (const juce::MidiMessageMetadata metadata : buffer)
            {
                if (metadata.numBytes == 3)
                {
                    juce::Logger::writeToLog(metadata.getMessage().getDescription());
                }
            }
        }
    };
}

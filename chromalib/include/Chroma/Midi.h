#pragma once


namespace Chroma
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

        static int distanceInCents(Chroma::NoteInfo& note_a, Chroma::NoteInfo& note_b)
        {
            auto a = (note_a.note * 100) + note_a.cents;
            auto b = (note_b.note * 100) + note_b.cents;

            return b - a;
        }

        static int getPitchBend(int distanceInCents)
        {
            DBG(distanceInCents);
            return 8192 + (static_cast<double> (distanceInCents) * 1.70666666);
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

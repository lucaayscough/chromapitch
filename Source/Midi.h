#pragma once


namespace Chroma
{

struct NoteInfo
{
    double frequency = 0;
    int midiNoteNumber = 0;
    juce::String noteName;
    int cents = 0;
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
};

}

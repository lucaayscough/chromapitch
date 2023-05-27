#pragma once


struct Variables
{
    // MIDI
    static const bool outputMidi = false;

    //
    static const int incrementFactor = 2;

    // MAIN WINDOW
    static const int windowWidth = 1000;
    static const int windowHeight = 600;

    // PRE-PROCESSING
    static const int minimumFrequency = 82;
    static const int maximumFrequency = 1312;
    static constexpr float rmsThreshold = 0.001f;
    static const int numFilters = 32;
    
    // GUI
    static const int headerHeight = 60;
    static const int lowerKeyBound = 21;
    static const int higherKeyBound = 109;
    static const int numBoxes = higherKeyBound - lowerKeyBound; 
    static const int noteBoxHeight = 40;
    static const int distanceThreshold = 20;
    
    // COLOURS
    static const juce::Colour black;
    static const juce::Colour green;
    static const juce::Colour white; 
    static const juce::Colour red;
    static const juce::Colour blue;
    static const juce::Colour lavender;
    static constexpr float gradientAlphaUpdateRate = 0.05f;
    static constexpr float gradientPosUpdateRate = 0.01f;
};



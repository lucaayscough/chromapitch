#pragma once


struct Variables
{
    static const bool outputMidi = true;
    static const int incrementFactor = 2;
    static const int windowWidth = 800;
    static const int windowHeight = 600;
    static const int minimumFrequency = 82;
    static const int maximumFrequency = 1312;
    static constexpr float rmsThreshold = 0.001f;
    
    static const int lowerKeyBound = 21;
    static const int higherKeyBound = 109;
    static const int numBoxes = higherKeyBound - lowerKeyBound; 
    static const int noteBoxHeight = 40;
    
    static const juce::Colour backgroundColour;
    static const juce::Colour boundingBoxColour;
    static const juce::Colour pitchLineColour; 
    static const juce::Colour textColour;
    static const int distanceThreshold = 20;
};



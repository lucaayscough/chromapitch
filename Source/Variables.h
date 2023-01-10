#pragma once


struct Variables
{
    static const int incrementFactor = 2;
    static const int windowWidth = 1600;
    static const int windowHeight = 800;
    static const int minimumFrequency = 50;
    
    static const int lowerKeyBound = 21;
    static const int higherKeyBound = 109;
    static const int numBoxes = higherKeyBound - lowerKeyBound; 
    static const int noteBoxHeight = 40;
};

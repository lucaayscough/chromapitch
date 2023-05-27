#include "Headers.h"


Header::Header() {}
Header::~Header() {}

void Header::paint(juce::Graphics& g) 
{
    g.fillAll(Variables::lavender);
}

void Header::resized() {}

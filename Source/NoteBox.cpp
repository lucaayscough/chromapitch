#include "Headers.h"


NoteBox::NoteBox() {}

NoteBox::~NoteBox() {}

void NoteBox::paint(juce::Graphics& g)
{       
    g.fillAll(juce::Colours::white);
    g.setColour(juce::Colours::red);
    g.drawLine(0, 0, getWidth(), 0, 1);
}

void NoteBox::resized() {}


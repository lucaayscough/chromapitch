#include "Headers.h"


NoteBox::NoteBox() {}

NoteBox::~NoteBox() {}

void NoteBox::paint(juce::Graphics& g)
{       
    g.fillAll(Variables::backgroundColour);
    g.setColour(Variables::boundingBoxColour);
    g.drawLine(0, 0, getWidth(), 0, 1);
    g.setColour(Variables::textColour);
    g.drawText(getComponentID(), getLocalBounds(), juce::Justification::centred, true);
}

void NoteBox::resized() {}


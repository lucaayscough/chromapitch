#include "Headers.h"


View::View() 
{
    for (int i = 0; i < Variables::numBoxes; ++i)
    {
        m_noteBoxes.add(new NoteBox);
        addAndMakeVisible(m_noteBoxes[i]);
        m_noteBoxes[i]->setComponentID(juce::MidiMessage::getMidiNoteName(Variables::higherKeyBound - i - 1, true, true, 4));
    }
}

View::~View() {}

void View::paint(juce::Graphics& g) {}

void View::resized()
{
    float noteBoxHeight = getHeight() / Variables::numBoxes;
    for (int i = 0; i < Variables::numBoxes; ++i)     
    {
        m_noteBoxes[i]->setBounds(0, i * noteBoxHeight, getWidth(), noteBoxHeight);
    }
}

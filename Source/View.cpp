#include "Headers.h"


View::View() 
{
    for (int i = 0; i < Variables::numBoxes; ++i)
    {
        m_noteBoxes.add(new NoteBox);
        addAndMakeVisible(m_noteBoxes[i]);
        m_noteBoxes[i]->setComponentID(juce::String(i));
    }
}

View::~View() {}

void View::paint(juce::Graphics& g) {}

void View::resized()
{
    for (int i = 0; i < Variables::numBoxes; ++i)     
    {
        m_noteBoxes[i]->setBounds(0, i * Variables::noteBoxHeight, getWidth(), Variables::noteBoxHeight);
    }
}

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

void View::update(chroma::NoteInfo& note)
{
    for (int i = 0; i < Variables::numBoxes; ++i)    
    {
        int index = Variables::numBoxes - i + Variables::lowerKeyBound - 1;
        
        if (note.note == index)
        {
            m_noteBoxes[i]->turnOn();
            float gradientPos = (note.cents + 50) / 100.f; 
            m_noteBoxes[i]->setGradientPos(gradientPos);
        }
        
        else
        {
            m_noteBoxes[i]->turnOff();
        }
        
        m_noteBoxes[i]->update();
    }
}

void View::paint(juce::Graphics& g)
{
    g.fillAll(Variables::black);
}

void View::resized()
{
    float noteBoxHeight = getHeight() / Variables::numBoxes;
    for (int i = 0; i < Variables::numBoxes; ++i)     
    {
        m_noteBoxes[i]->setBounds(0, i * noteBoxHeight, getWidth(), noteBoxHeight);
    }
}

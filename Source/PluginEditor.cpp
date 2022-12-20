#include "Headers.h"


ChromaPitchAudioProcessorEditor::ChromaPitchAudioProcessorEditor (ChromaPitchAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(Variables::windowWidth, Variables::windowHeight);
    
    line.add(new Line);
    line.add(new Line);

    line[1]->colour = juce::Colours::red;
    
    addAndMakeVisible(line[0]);
    addAndMakeVisible(line[1]);
    
    startTimerHz(60);
}

ChromaPitchAudioProcessorEditor::~ChromaPitchAudioProcessorEditor() {}

void ChromaPitchAudioProcessorEditor::paint(juce::Graphics& g) {}

void ChromaPitchAudioProcessorEditor::resized() {}

void ChromaPitchAudioProcessorEditor::timerCallback()
{
    if (iter == 0) {
        line[0]->unfreeze();
    }
    
    else if (iter == getWidth())
    {
        line[1]->unfreeze();
    }
    
    if (posX0 < -getWidth())
    {
        posX0 = 800.f;
    }
    
    if (posX1 < -getWidth())
    {
        posX1 = 800.f;
    }
    
    line[0]->setBounds(posX0, 0, getWidth(), getHeight());
    line[1]->setBounds(posX1, 0, getWidth(), getHeight());
    
    posX0 -= Variables::incrementFactor;
    posX1 -= Variables::incrementFactor;
    
    iter += Variables::incrementFactor;
    
    if (iter > getWidth() * 2)
    {
        iter = 0;
    }
    
    repaint();
}

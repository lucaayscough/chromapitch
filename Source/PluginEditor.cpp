#include "Headers.h"


ChromaPitchAudioProcessorEditor::ChromaPitchAudioProcessorEditor (ChromaPitchAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(Variables::windowWidth, Variables::windowHeight);
    
    for (int i = 0; i < Variables::windowWidth / Variables::incrementFactor; ++i)
    {
        lines.add(new juce::Line<float>);
    }
    
    startTimerHz(60);
}

ChromaPitchAudioProcessorEditor::~ChromaPitchAudioProcessorEditor() {}

void ChromaPitchAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
   
    g.setColour(juce::Colours::orange);
    g.fillPath(path);
}

void ChromaPitchAudioProcessorEditor::resized() {}

void ChromaPitchAudioProcessorEditor::timerCallback()
{
    auto frequency = audioProcessor.yin.getNextFrequency();
    
    frequencies.insert(0, frequency);
    
    if (frequencies.size() > getWidth() / Variables::incrementFactor)
    {
        frequencies.remove(frequencies.size() - 1);
    }
    
    path.clear();
    
    for (int i = 0; i < frequencies.size(); ++i)
    {
        if (frequencies[i] != -1)
        {
            lines[i]->setStart(getWidth() - ((i + 1) * Variables::incrementFactor), getHeight() / 2 - frequencies[i]);
            lines[i]->setEnd(getWidth() - ((i + 1) * Variables::incrementFactor) + Variables::incrementFactor, getHeight() / 2 - frequencies[i]);
            
            path.addLineSegment(*lines[i], 5);
        }
    } 

    repaint();
}

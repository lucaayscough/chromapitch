#include "Headers.h"


PitchLine::PitchLine()
{
    for (int i = 0; i < Variables::windowWidth / Variables::incrementFactor; ++i)
    {
        lines.add(new juce::Line<float>);
    }
}

PitchLine::~PitchLine() {}

void PitchLine::update(float frequency)
{
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
}

void PitchLine::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::orange);
    g.fillPath(path);
}

void PitchLine::resized() {}

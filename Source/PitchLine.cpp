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

            int note = (12 * log(frequencies[i] / 220.0) / log(2.0)) + 57;

            int posStartX = getWidth() - ((i + 1) * Variables::incrementFactor);
            int posStartY = (Variables::higherKeyBound - note - 1) * Variables::noteBoxHeight;
            
            int posEndX = posStartX + Variables::incrementFactor;
            int posEndY = posStartY;

            if (i > 0) 
            {
                for (int validFreq = 1; validFreq < 21; ++validFreq)
                {
                    if (frequencies[i - validFreq] != -1)        
                    {
                        
                        note = (12 * log(frequencies[i - validFreq] / 220.0) / log(2.0)) + 57;

                        posStartX = getWidth() - ((i + 1 - validFreq) * Variables::incrementFactor);
                        posStartY = (Variables::higherKeyBound - note - 1) * Variables::noteBoxHeight;
                    } 
                }
            }

            lines[i]->setStart(posStartX, posStartY);
            lines[i]->setEnd(posEndX, posEndY);
            
            
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

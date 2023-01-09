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

            int note = Chroma::Midi::frequencyToMidi(frequencies[i]);
            int cents = Chroma::Midi::centsFromNearestNote(frequencies[i]);

            int posStartX = getWidth() - ((i + 1) * Variables::incrementFactor);
            int posStartY = (Variables::higherKeyBound - note) * Variables::noteBoxHeight - Variables::noteBoxHeight / 2 - ((cents / 50.0) * (Variables::noteBoxHeight / 2.0));

            int posEndX = posStartX + Variables::incrementFactor;
            int posEndY = posStartY;
            
            if (i > 0) 
            {
                for (int validFreq = 1; validFreq < 100; ++validFreq)
                {
                    if (i - validFreq < 0)
                        break;

                    else if (frequencies[i - validFreq] != -1)        
                    {
                        note = Chroma::Midi::frequencyToMidi(frequencies[i - validFreq]);
                        
                        posStartX = getWidth() - ((i + 1 - validFreq) * Variables::incrementFactor);
                        posStartY = (Variables::higherKeyBound - note) * Variables::noteBoxHeight - Variables::noteBoxHeight / 2 - ((cents / 50.0) * (Variables::noteBoxHeight / 2.0));
                        break;
                    } 
                }
            }

            lines[i]->setStart(posStartX, posStartY);
            lines[i]->setEnd(posEndX, posEndY);
            
            path.addLineSegment(*lines[i], 6);
        }
    } 
}

void PitchLine::paint(juce::Graphics& g)
{
    g.setColour(juce::Colours::orange);
    g.fillPath(path);
}

void PitchLine::resized() {}

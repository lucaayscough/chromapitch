#include "Headers.h"


Line::Line() {}

Line::~Line() {}

void Line::setFrequency(float frequencyToUse)                   { frequency = frequencyToUse; }

bool Line::isFrozen()
{
    return frozen;
}

void Line::freeze()
{
    frozen = true;
}

void Line::unfreeze()
{
    frozen = false;
    path.clear();
}

void Line::paint(juce::Graphics &g)
{
    if (step > getWidth())
    {
        freeze();
        step = 0;
    }
    
    if (!frozen)
    {
        juce::Line<float> line;
        
        line.setStart(step, (getHeight() / 2.f) - (lineThickness / 2.f));
        
        step += Variables::incrementFactor;
        
        line.setEnd(step, (getHeight() / 2.f) - (lineThickness / 2.f));
        
        path.addLineSegment(line, lineThickness);
    }
    
    g.setColour(colour);
    g.fillPath(path);
}

void Line::resized() {}

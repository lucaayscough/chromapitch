#include "Headers.h"


PitchLine::PitchLine() {}

PitchLine::~PitchLine() {}

void PitchLine::update(float frequency)
{
    if (frequency == -1)
    {
        m_posY.insert(0, -1);
    }

    else
    {
        int note = Chroma::Midi::frequencyToMidi(frequency);
        int cents = Chroma::Midi::centsFromNearestNote(frequency);
        
        int posY = (Variables::higherKeyBound - note) * Variables::noteBoxHeight - Variables::noteBoxHeight / 2 - ((cents / 50.0) * (Variables::noteBoxHeight / 2.0));

        m_posY.insert(0, posY);
    }
    
    if (m_posY.size() > getWidth() / Variables::incrementFactor)
    {
        m_posY.remove(m_posY.size() - 1);
    }
    
    m_path.clear();
    
    int posX, nextPosY;
    juce::Line<float> line;

    for (int i = 0; i < m_posY.size(); ++i)
    {
        if (m_posY[i] != -1)
        {
            posX = getWidth() - (i * Variables::incrementFactor);

            // Search for next viable Y.
            nextPosY = m_posY[i]; 

            for (int y = 1; y + i < m_posY.size() && y < 50; ++y)
            {
                if (m_posY[i + y] != -1)
                {
                    nextPosY = m_posY[i + y];
                    break;
                }
            } 

            line.setStart(posX, m_posY[i]);
            line.setEnd(posX - Variables::incrementFactor, nextPosY);
            
            m_path.addLineSegment(line, 4);

        }
    } 
}

void PitchLine::paint(juce::Graphics& g)
{
    g.setColour(Variables::pitchLineColour);
    g.fillPath(m_path);
}

void PitchLine::resized() {}

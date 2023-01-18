#include "Headers.h"


PitchLine::PitchLine() {}

PitchLine::~PitchLine() {}

float PitchLine::getCurrentY()
{
    if (!m_posY.isEmpty())
    {
        return m_posY[0];
    }

    else
    {
        return -1;
    }
}

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
    
    int posX;

    for (int i = 0; i < m_posY.size(); ++i)
    {
        if (m_posY[i] != -1)
        {
            posX = getWidth() - (i * Variables::incrementFactor);

            juce::Point<float> p(posX, m_posY[i]);

            if (m_path.isEmpty() || p.getDistanceFrom(m_path.getCurrentPosition()) > Variables::distanceThreshold)
            {
                m_path.startNewSubPath(p);
            }

            m_path.lineTo(p);
        }
    }

    repaint();
}

void PitchLine::paint(juce::Graphics& g)
{
    g.setColour(Variables::pitchLineColour);
    g.strokePath(m_path, juce::PathStrokeType(3, juce::PathStrokeType::beveled, juce::PathStrokeType::rounded));
}

void PitchLine::resized() {}

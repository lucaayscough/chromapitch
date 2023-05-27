#include "Headers.h"


NoteBox::NoteBox()
{
    m_gradient.addColour(0.0, Variables::red);
    m_gradient.addColour(0.5, Variables::green);
    m_gradient.addColour(1.0, Variables::red);
}

NoteBox::~NoteBox() {}

void NoteBox::turnOn()
{
    m_isOn = true;
}

void NoteBox::turnOff()
{
    m_isOn = false;
}

void NoteBox::setGradientPos(float gradientPos)
{
    if (gradientPos > m_gradientPos)
    {
        m_gradientPos += Variables::gradientPosUpdateRate;
    }

    else if (gradientPos < m_gradientPos)
    {
        m_gradientPos -= Variables::gradientPosUpdateRate;
    }

    if (m_gradientPos < 0.f)
    {
        m_gradientPos = 0.f;
    }

    else if (m_gradientPos > 1.f)
    {
        m_gradientPos = 1.f;
    }
}

void NoteBox::update()
{
    if (m_isOn)
    {
        m_alpha += Variables::gradientAlphaUpdateRate;
    }

    if (!m_isOn && m_alpha > 0.f)
    {
        m_alpha -= Variables::gradientAlphaUpdateRate;
    }

    if (m_alpha < 0.f)
    {
        m_alpha = 0.f;
    }

    else if (m_alpha > 1.f)
    {
        m_alpha = 1.f;
    }
    
    repaint();
}

void NoteBox::paint(juce::Graphics& g)
{
    auto colour = m_gradient.getColourAtPosition(m_gradientPos);
    g.setColour(colour);
    g.setOpacity(m_alpha * m_alpha);
    g.fillAll();

    g.setColour(Variables::lavender);
    g.drawText(getComponentID(), getLocalBounds(), juce::Justification::right, true);
    
}

void NoteBox::resized() {}


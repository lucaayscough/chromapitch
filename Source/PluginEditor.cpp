#include "Headers.h"


ChromaPitchAudioProcessorEditor::ChromaPitchAudioProcessorEditor (ChromaPitchAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(Variables::windowWidth, Variables::windowHeight);
    setResizable(true, true);

    startTimerHz(60);

    addAndMakeVisible(m_view);
    addAndMakeVisible(m_pitchLine);
}

ChromaPitchAudioProcessorEditor::~ChromaPitchAudioProcessorEditor() {}

void ChromaPitchAudioProcessorEditor::paint(juce::Graphics& g) {}

void ChromaPitchAudioProcessorEditor::resized()
{
    m_view.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * m_noteBoxHeight);
    m_pitchLine.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * m_noteBoxHeight);  
}

void ChromaPitchAudioProcessorEditor::timerCallback()
{
    auto frequency = audioProcessor.m_pitchDetector.getNextFrequency();
    m_pitchLine.update(frequency);
 
    if (m_pitchLine.getCurrentY() < -m_pitchLine.getY() && m_pitchLine.getCurrentY() != -1)
    {
        ++m_scrollPosY;
        updateBounds();
    }

    else if (m_pitchLine.getCurrentY() > -m_pitchLine.getY() + Variables::windowHeight && m_pitchLine.getCurrentY() != -1)
    {
        --m_scrollPosY;
        updateBounds();
    }
}

void ChromaPitchAudioProcessorEditor::mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel)
{
    m_scrollPosY += wheel.deltaY * 80;      

    if (m_scrollPosY < -(Variables::numBoxes * m_noteBoxHeight - getHeight()))
    {
        m_scrollPosY = -(Variables::numBoxes * m_noteBoxHeight - getHeight());
    }
    
    else if (m_scrollPosY > 0)
    {
        m_scrollPosY = 0;
    }

    updateBounds();
}

void ChromaPitchAudioProcessorEditor::mouseMagnify(const juce::MouseEvent& event, float scaleFactor)
{
    if (scaleFactor > 1.0f && m_noteBoxHeight < 60.0f)
    {
        m_noteBoxHeight += 1.0f;
        m_scrollPosY -= Variables::numBoxes;
    }
    
    else if (scaleFactor < 1.0f && m_noteBoxHeight > 20.0f)
    {
        m_noteBoxHeight -= 1.0f;
        m_scrollPosY += Variables::numBoxes;
    }

    updateBounds();
}

void ChromaPitchAudioProcessorEditor::updateBounds()
{
    m_view.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * m_noteBoxHeight);
    m_pitchLine.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * m_noteBoxHeight);  
    
    m_view.repaint();
    m_pitchLine.repaint();
}

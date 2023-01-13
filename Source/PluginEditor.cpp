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
    m_view.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * Variables::noteBoxHeight);
    m_pitchLine.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * Variables::noteBoxHeight);  
}

void ChromaPitchAudioProcessorEditor::timerCallback()
{
    auto frequency = audioProcessor.m_yin.getNextFrequency();
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

    repaint();
}

void ChromaPitchAudioProcessorEditor::mouseWheelMove(const juce::MouseEvent& event, const juce::MouseWheelDetails& wheel)
{
    m_scrollPosY += wheel.deltaY * 80;      

    if (m_scrollPosY < -(Variables::numBoxes * Variables::noteBoxHeight - getHeight()))
    {
        m_scrollPosY = -(Variables::numBoxes * Variables::noteBoxHeight - getHeight());
    }
    
    else if (m_scrollPosY > 0)
    {
        m_scrollPosY = 0;
    }

    updateBounds();
}

void ChromaPitchAudioProcessorEditor::updateBounds()
{
    m_view.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * Variables::noteBoxHeight);
    m_pitchLine.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * Variables::noteBoxHeight);  
}

#include "Headers.h"


ChromaPitchAudioProcessorEditor::ChromaPitchAudioProcessorEditor (ChromaPitchAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(Variables::windowWidth, Variables::windowHeight);
    
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
    auto frequency = audioProcessor.yin.getNextFrequency();
    m_pitchLine.update(frequency);

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

    m_view.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * Variables::noteBoxHeight);
    m_pitchLine.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * Variables::noteBoxHeight);  
}

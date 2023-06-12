#include "Headers.h"


ChromaPitchAudioProcessorEditor::ChromaPitchAudioProcessorEditor (ChromaPitchAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(Variables::windowWidth, Variables::windowHeight);
    setResizable(true, true);

    startTimerHz(60);

    addAndMakeVisible(m_header);
    addAndMakeVisible(m_view);
    addAndMakeVisible(m_pitchLine);

    m_header.setAlwaysOnTop(true);
}

ChromaPitchAudioProcessorEditor::~ChromaPitchAudioProcessorEditor() {}

void ChromaPitchAudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(Variables::blue);
}

void ChromaPitchAudioProcessorEditor::resized()
{
    updateBounds(); 
}

void ChromaPitchAudioProcessorEditor::timerCallback()
{
    auto note = audioProcessor.getLastNote();
    
    m_view.update(note);
    m_pitchLine.update(note);
 
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
    auto y = event.getMouseDownY();
    y += -m_scrollPosY;
    
    float numBoxes = y / m_noteBoxHeight;

    if (scaleFactor > 1.0f && m_noteBoxHeight < 60.0f)
    {
        m_noteBoxHeight += 0.1f;
        m_scrollPosY -= numBoxes * 0.1f;
    }
    
    else if (scaleFactor < 1.0f && m_noteBoxHeight > 20.0f)
    {
        m_noteBoxHeight -= 0.1f;
        m_scrollPosY += numBoxes * 0.1f;
    }
    
    updateBounds();
}

void ChromaPitchAudioProcessorEditor::updateBounds()
{
    m_header.setBounds(0, 0, getWidth(), Variables::headerHeight);
    m_view.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * m_noteBoxHeight);
    m_pitchLine.setBounds(0, m_scrollPosY, getWidth(), Variables::numBoxes * m_noteBoxHeight);  

    m_header.repaint(); 
    m_view.repaint();
    m_pitchLine.repaint();
}

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
    m_view.setBounds(getBounds());
    m_pitchLine.setBounds(getBounds());  
}

void ChromaPitchAudioProcessorEditor::timerCallback()
{
    auto frequency = audioProcessor.yin.getNextFrequency();
    m_pitchLine.update(frequency);
    DBG(frequency);

    repaint();
}

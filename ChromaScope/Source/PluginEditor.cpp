#include "Headers.h"


AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    setSize (400, 400);
    startTimerHz (60);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    
    auto& scopeRef = processorRef.getScopeProcessor();
    auto& bufferRef = scopeRef.getRingBuffer();

    for (auto point : bufferRef)
    {
        g.setColour (juce::Colours::red);
        g.fillEllipse (200 + (200 * point.x), 200 + (200 * point.y), 10, 10);
    }

}

void AudioPluginAudioProcessorEditor::resized() {}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    repaint();
}

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

    float a = 1.f;
    float delta = 1.f / (float)bufferRef.getSize();

    for (auto point : bufferRef)
    {
    
        a = a - delta;

        g.setColour (juce::Colours::red.withAlpha(a));
        g.fillEllipse (200 + (200 * point.x), 200 + (200 * point.y), 2, 2);
    }
}

void AudioPluginAudioProcessorEditor::resized() {}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    repaint();
}

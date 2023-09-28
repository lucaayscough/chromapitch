#include "Headers.h"


AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    setSize (1000, 800);
    startTimerHz (60);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

void AudioPluginAudioProcessorEditor::resized() {}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    repaint();
}

void AudioPluginAudioProcessorEditor::mouseDown (const juce::MouseEvent &event)
{
    juce::ignoreUnused (event);
    auto& plugins = processorRef.getPlugins();
    juce::ignoreUnused (plugins);
}

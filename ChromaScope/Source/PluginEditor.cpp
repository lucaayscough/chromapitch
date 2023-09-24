#include "Headers.h"


AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    setSize (1000, 1000);
    startTimerHz (60);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {}

void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Background color
    g.fillAll (juce::Colours::black);

    // Draw a subtle grid
    g.setColour (juce::Colours::grey.withAlpha(0.2f));
    for (int i = 0; i < getWidth(); i += 20)
        g.drawLine (i, 0, i, getHeight(), 0.5f);
    for (int i = 0; i < getHeight(); i += 20)
        g.drawLine (0, i, getWidth(), i, 0.5f);

    auto& scopeRef = processorRef.getScopeProcessor();
    auto& bufferRef = scopeRef.getRingBuffer();

    float a = 1.f;
    float delta = 1.f / static_cast<float>(bufferRef.getSize());

    auto centerX = getWidth() * 0.5f;
    auto centerY = getHeight() * 0.5f;
    auto radius = juce::jmin(centerX, centerY) * 0.8f;

    for (auto point : bufferRef)
    {
        a = a - delta;

        // Gradient from blue to red for the glow effect
        auto glowColour = juce::Colour::fromFloatRGBA(1.0f - a, 0, a, a);
        juce::ColourGradient gradient(glowColour, centerX + (radius * point.x),
                                      centerY + (radius * point.y),
                                      juce::Colours::transparentBlack,
                                      centerX + (radius * point.x) + 5.0f,
                                      centerY + (radius * point.y) + 5.0f, false);

        g.setGradientFill(gradient);
        
        g.fillEllipse(centerX + (radius * point.x) - 5,
                      centerY + (radius * point.y) - 5, 
                      10, 10);
    }
}

void AudioPluginAudioProcessorEditor::resized() {}

void AudioPluginAudioProcessorEditor::timerCallback()
{
    repaint();
}

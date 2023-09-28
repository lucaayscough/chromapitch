#pragma once


class AudioPluginAudioProcessorEditor : public juce::AudioProcessorEditor, juce::Timer
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&, StateManager& stateManager);
    ~AudioPluginAudioProcessorEditor() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    void mouseDown (const juce::MouseEvent& event) override;

    void addEffectNode(juce::Point<int> position);

private:
    void timerCallback() override;

private:
    AudioPluginAudioProcessor& processorRef;
    StateManager& m_stateManager;
    std::unique_ptr<PluginWindow> m_pluginWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};

#pragma once


class PluginWindow : public juce::DocumentWindow
{
public:
    PluginWindow (const juce::String& name, juce::AudioProcessor& processor);
    ~PluginWindow() override;

    juce::AudioProcessorEditor* createProcessorEditor();

    void closeButtonPressed() override;

private:
    juce::AudioProcessor& m_processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginWindow)
};

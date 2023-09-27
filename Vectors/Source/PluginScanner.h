#pragma once


class PluginScanner : public juce::Thread 
{
public:
    PluginScanner();
    ~PluginScanner() override;

    void run() override;

private:
    juce::AudioUnitPluginFormat m_formatManager;
    juce::KnownPluginList m_knownPluginList;
    juce::File m_deadMansPedalFile;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginScanner)
};

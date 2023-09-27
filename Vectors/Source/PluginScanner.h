#pragma once


class PluginScanner 
{
public:
    PluginScanner();
    ~PluginScanner();

private:
    juce::AudioUnitPluginFormat m_formatManager;
    juce::KnownPluginList m_knownPluginList;
    juce::File m_deadMansPedalFile;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginScanner)
};

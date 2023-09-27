#include "Headers.h"


PluginScanner::PluginScanner() : juce::Thread ("PluginScannerThread") {}

PluginScanner::~PluginScanner() {}

void PluginScanner::run()
{
    DBG ("Scanning plugins...");

    //m_formatManager.addDefaultFormats();

    m_deadMansPedalFile = Globals::deadMansPedalFilePath;
    m_deadMansPedalFile.create();

    juce::PluginDirectoryScanner m_pluginDirectoryScanner (
        m_knownPluginList,
        m_formatManager,
        m_formatManager.getDefaultLocationsToSearch(),
        true,
        m_deadMansPedalFile,
        false
    );

    juce::File xmlFile = Globals::knownPluginListPath;

    // Read plugin list from disk.

    if (xmlFile.existsAsFile())
    {
        std::unique_ptr<juce::XmlElement> xml = juce::XmlDocument::parse(xmlFile);

        if (xml != nullptr)
        {
            m_knownPluginList.recreateFromXml(*xml);
        }
    }

    juce::PluginDirectoryScanner::applyBlacklistingsFromDeadMansPedal (m_knownPluginList, m_deadMansPedalFile);

    while (m_pluginDirectoryScanner.getProgress() < 1.f)
    {
        auto fileName = m_pluginDirectoryScanner.getNextPluginFileThatWillBeScanned();
        m_pluginDirectoryScanner.scanNextFile(true, fileName);

        DBG (fileName);
        DBG (m_pluginDirectoryScanner.getProgress());

        // Save plugin list to disk.

        std::unique_ptr<juce::XmlElement> xml = m_knownPluginList.createXml();

        if (xml != nullptr)
        {
            xml->writeToFile(xmlFile, "");
        }

        if (threadShouldExit())
        {
            return;
        }
    }
}

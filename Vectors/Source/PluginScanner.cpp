#include "Headers.h"


PluginScanner::PluginScanner()
{
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

    if (xmlFile.existsAsFile())
    {
        // Read XML from file
        std::unique_ptr<juce::XmlElement> xml = juce::XmlDocument::parse(xmlFile);

        // Check if the XML is valid
        if (xml != nullptr)
        {
            // Restore knownPluginList from XML
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

        std::unique_ptr<juce::XmlElement> xml = m_knownPluginList.createXml();

        // Check if the XML is not null
        if (xml != nullptr)
        {
            // Write XML to file
            juce::File xmlFile = (Globals::knownPluginListPath);
            xml->writeToFile(xmlFile, "");
        }
    }
}

PluginScanner::~PluginScanner()
{
}

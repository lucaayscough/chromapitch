#include "Headers.h"



#if JUCE_MAC
  const juce::String Globals::rootPath = "~/Library/Application Support/Chroma Audio/Vectors/";       
#else
  const juce::String Globals::rootPath = "";
#endif

const juce::String Globals::deadMansPedalFilePath = rootPath + "deadMansPedalFile.txt";
const juce::String Globals::knownPluginListPath = rootPath + "knownPluginList.xml";

#include "Headers.h"


Header::Header()
{
    juce::Image logo = juce::ImageCache::getFromMemory (BinaryData::logo_png, BinaryData::logo_pngSize);
    m_Logo.setImage(logo, juce::RectanglePlacement::xMid);
    addAndMakeVisible(m_Logo);
}
Header::~Header() {}

void Header::paint(juce::Graphics& g) 
{
    g.fillAll(Variables::lavender);
}

void Header::resized()
{
    m_Logo.setBounds(getLocalBounds().withTrimmedTop(Variables::headerTrim).withTrimmedLeft(Variables::headerTrim).withTrimmedBottom(Variables::headerTrim));
}

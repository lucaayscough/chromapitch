#include "Headers.h"


Header::Header()
{
    juce::File img("/Users/lucaayscough/Work/Chroma Audio/Chroma Pitch/logo.png");
    juce::Image imgFromFile = juce::ImageFileFormat::loadFrom(img);
    m_Logo.setImage(imgFromFile, juce::RectanglePlacement::xMid);
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

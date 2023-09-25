#include "Headers.h"


//------------------------------------------------------------//
// Constructors and destructors.

TopBar::TopBar(){
    juce::File img(Variables::getLogoPath());
    juce::Image imgFromFile = juce::ImageFileFormat::loadFrom(img);
    m_LogoImage.setImage(imgFromFile, juce::RectanglePlacement::xLeft);
    addAndMakeVisible(m_LogoImage);
}

TopBar::~TopBar(){}

//------------------------------------------------------------//
// View methods.

void TopBar::paint(juce::Graphics& g){
    g.fillAll(Variables::EDITOR_BG_COLOUR);
}

void TopBar::resized(){
    // TODO:
    // Add variables for values.
    
    m_LogoImage.setBounds(getLocalBounds().withTrimmedLeft(6).withTrimmedTop(6).withTrimmedBottom(6));
}

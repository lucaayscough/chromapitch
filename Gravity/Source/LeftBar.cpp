#include "Headers.h"


//------------------------------------------------------------//
// Constructors and destructors.

LeftBar::LeftBar(juce::OwnedArray<Map>& maps)
    :   m_MapsRef(maps){
    m_MapButtons.ensureStorageAllocated(Variables::NUM_MAPS);

    for(int i = 0; i < Variables::NUM_MAPS; i++){
        m_MapButtons.add(new MapButton(m_MapsRef, juce::String(i)));
        addAndMakeVisible(m_MapButtons[i]);
    }
}

LeftBar::~LeftBar(){}

//------------------------------------------------------------//
// View methods.

void LeftBar::paint(juce::Graphics& g){
    g.fillAll(Variables::EDITOR_BG_COLOUR);
}

void LeftBar::resized(){
    auto r = getLocalBounds().withTrimmedTop(Variables::LEFT_BAR_TOP_BOUNDARY).withTrimmedBottom(Variables::LEFT_BAR_BOTTOM_BOUNDARY);
    auto button_height = r.getHeight() / Variables::NUM_MAPS;

    for(MapButton* map_button : m_MapButtons){
        auto map_button_area = r.removeFromTop(button_height);
        map_button->setBounds(map_button_area);
    }
}

//------------------------------------------------------------//
// Interface methods.

void LeftBar::setListeners(){
    for(MapButton* map_button : m_MapButtons){
        map_button->setListeners();
    }
}



#include "Headers.h"


//------------------------------------------------------------//
// Constructors and destructors.

MapButton::MapButton(juce::OwnedArray<Map>& maps, const juce::String& id)
    :   m_MapsRef(maps){
    setComponentID(id);
    m_MapImage.setInterceptsMouseClicks(false, false);
    addAndMakeVisible(m_MapImage);
}

MapButton::~MapButton(){}

//------------------------------------------------------------//
// Init methods.

void MapButton::setListeners(){
    getMap().m_UpdateImage.addListener(this);
}

//------------------------------------------------------------//
// View methods.

void MapButton::paint(juce::Graphics& g){
    if(getMap().isVisible())
        g.fillAll(Variables::MAP_BUTTON_BG_COLOUR_1);
    else
        g.fillAll(Variables::EDITOR_BG_COLOUR);
}

void MapButton::resized(){
    setImage();
}

//------------------------------------------------------------//
// Interface methods.

int MapButton::getButtonIndex(){return getComponentID().getIntValue();}
Map& MapButton::getMap(){return *m_MapsRef[getButtonIndex()];}

void MapButton::setImage(){
    Map& map = getMap();
    m_MapImage.setImage(map.createComponentSnapshot(map.getLocalBounds(), true, 0.1f), juce::RectanglePlacement::xLeft);
    m_MapImage.setBounds(getLocalBounds().withTrimmedLeft(Variables::LEFT_BAR_MAP_BOUNDARY).withTrimmedTop(Variables::LEFT_BAR_MAP_BOUNDARY).withTrimmedBottom(Variables::LEFT_BAR_MAP_BOUNDARY));
    getMap().m_UpdateImage = false;
}

//------------------------------------------------------------//
// Controller methods.

void MapButton::mouseDown(const juce::MouseEvent& e){
    juce::ignoreUnused(e);
    
    for(int i = 0; i < Variables::NUM_MAPS; i++){
        if(i == getButtonIndex()){
            m_MapsRef[i]->setVisible(true);
            m_MapsRef[i]->setInterceptsMouseClicks(true, true);
        }
        else{
            m_MapsRef[i]->setVisible(false);
            m_MapsRef[i]->setInterceptsMouseClicks(false, false);
        }
    }

    getParentComponent()->repaint();
}

//------------------------------------------------------------//
// Callback methods.

void MapButton::valueChanged(juce::Value& v){
    juce::ignoreUnused(v);
    setImage(); 
}

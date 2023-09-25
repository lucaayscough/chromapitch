#include "Headers.h"


//------------------------------------------------------------//
// Constructors and destructors.

Sun::Sun(AudioContainer& audiocontainer, Parameters& parameters, ControlPanel& controlpanel)
    :   Astro(Parameters::M_SUN_ID, audiocontainer, parameters, controlpanel){}

Sun::~Sun(){}

//------------------------------------------------------------//
// View methods.

void Sun::resized(){
    draw();
    setPosXY(getX(), getY());
}

void Sun::draw(){
    setSize(getDiameterWithClipBoundary(), getDiameterWithClipBoundary());
    setCentreRelative(0.5, 0.5);
}

//------------------------------------------------------------//
// Interface methods.

juce::ValueTree Sun::getState(){
    auto id = getParentComponent()->getComponentID();
    auto mapNode = m_ParametersRef.getMapNode(id);
    return m_ParametersRef.getSunNode(mapNode);
}

//------------------------------------------------------------//
// Controller methods.

void Sun::mouseDown(const juce::MouseEvent& e){
    if(e.getNumberOfClicks() > 1 && e.mods.isLeftButtonDown()){
        generateSample();
    }

    else if(e.mods.isLeftButtonDown() && e.mouseWasClicked()){
        playSample();
    }
}

#include "Headers.h"


//--------------------------------------------------//
// Constructors and destructors.

ControlPanel::ControlPanel(Parameters& parameters)
    :   m_ParametersRef(parameters){
    setAlwaysOnTop(true);
}

ControlPanel::~ControlPanel(){}

//--------------------------------------------------//
// View methods.

void ControlPanel::paint(juce::Graphics& g){
    g.setColour(juce::Colours::blue);
    float x = (float)m_State.getProperty(Parameters::posXProp) + (m_Component->getWidth() - m_Width) / 2.0f;
    float y = (float)m_State.getProperty(Parameters::posYProp) - 50.0f;
    g.fillRect(x, y, m_Width, m_Height);
}

void ControlPanel::resized(){}

void ControlPanel::show(juce::ValueTree node, juce::Component* component){
    setVisible(true);
    m_State = node;
    m_Component = component;
}

void ControlPanel::unshow(){
    m_Component = nullptr;
    setVisible(false);
}

//--------------------------------------------------//
// Controller methods.

void ControlPanel::visibilityChanged(){
    repaint();
}

bool ControlPanel::hitTest(int x, int y){
    if(getX() < x && getX() + m_Width > x && getY() < y && getY() + m_Height > y){return true;}
    else{return false;}
}

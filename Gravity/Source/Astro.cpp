#include "Headers.h"


//--------------------------------------------------//
// Constructors and destructors.

Astro::Astro(juce::String& id, AudioContainer& audiocontainer, Parameters& parameters, ControlPanel& controlpanel)
    :   m_AudioContainerRef(audiocontainer), m_ParametersRef(parameters), m_ControlPanelRef(controlpanel){
    setComponentID(id);
    setListeners();
    setGradients();
}

Astro::~Astro(){}

//--------------------------------------------------//
// Init methods.

void Astro::setListeners(){
    m_Animator.m_AreaShift.addListener(this);
}

void Astro::setGradients(){
    m_ColourGradient.addColour((double)0.0, juce::Colour(255, 255, 255));
    m_ColourGradient.addColour((double)0.2, juce::Colour(255, 237, 63));
    m_ColourGradient.addColour((double)0.4, juce::Colour(255, 141, 0));
    m_ColourGradient.addColour((double)0.6, juce::Colour(255, 81, 0));
    m_ColourGradient.addColour((double)0.8, juce::Colour(241, 25, 25));
    m_ColourGradient.addColour((double)1.0, juce::Colour(212, 28, 28));
}

//--------------------------------------------------//
// View methods.

void Astro::paint(juce::Graphics& g){
    if(m_Animator.m_IsCreated){
        float shift = m_Animator.getDiameterShift(getArea());

        paintCircle(
            ((float)getClipBoundary() - shift) / 2.0f,
            (float)getDiameter() + shift, g
        );
    }
    else{
        paintCircle(
            (float)getRadiusWithClipBoundary() - m_Animator.getCreationRadius(),
            m_Animator.getCreationDiameter(), g
        );
    }
}

void Astro::paintCircle(float boundary_shift, float diameter, juce::Graphics& g){
    g.setColour(Variables::MAP_BG_COLOUR);
    g.fillEllipse(
        boundary_shift - Variables::DISTANCE_BOUNDARY / 2.0f,
        boundary_shift - Variables::DISTANCE_BOUNDARY / 2.0f,
        diameter + Variables::DISTANCE_BOUNDARY,
        diameter + Variables::DISTANCE_BOUNDARY
    );

    if(getState().getProperty(Parameters::isActiveProp)){
        g.setColour(juce::Colours::green);
    }
    else{
        double max_distance = sqrt((double)(pow(getParentWidth() / 2, 2)) + (double)(pow(getParentHeight() / 2, 2)));
        double pos = (getDistance(getCentreX(), getCentreY(), getParentWidth() / 2, getParentHeight() / 2)) / max_distance;
        g.setColour(m_ColourGradient.getColourAtPosition(pos));
    }

    g.fillEllipse(boundary_shift, boundary_shift, diameter, diameter);
}

void Astro::draw(){setBounds(getPosX(), getPosY(), getDiameterWithClipBoundary(), getDiameterWithClipBoundary());}
void Astro::draw(const int diameter, const int x, const int y){setBounds(x, y, diameter + getClipBoundary(), diameter + getClipBoundary());}

//--------------------------------------------------//
// Interface methods.

void Astro::setArea(const float area){getState().setProperty(Parameters::areaProp, area, nullptr);}

void Astro::setPosXY(const int x, const int y){
    getState().setProperty(Parameters::posXProp, x, nullptr);
    getState().setProperty(Parameters::posYProp, y, nullptr);
    setCentrePosXY(x + getRadius(), y + getRadius());
}

void Astro::setCentrePosXY(const int x, const int y){
    getState().setProperty(Parameters::posCentreXProp, x + getClipBoundary() / 2, nullptr);
    getState().setProperty(Parameters::posCentreYProp, y + getClipBoundary() / 2, nullptr);
}

juce::ValueTree Astro::getMapNode(){return m_ParametersRef.getMapNode(getState());}
float Astro::getArea(){return getState().getProperty(Parameters::areaProp);}
int Astro::getDiameter(){return (int)(round((sqrt(getArea() / Variables::PI) * 2.0f) / 2.0f) * 2.0f);}
int Astro::getDiameterWithClipBoundary(){return getDiameter() + getClipBoundary();}
int Astro::getRadius(){return getDiameter() / 2;}
int Astro::getRadiusWithClipBoundary(){return (getDiameter() + getClipBoundary()) / 2;}
int Astro::getPosX(){return getState().getProperty(Parameters::posXProp);}
int Astro::getPosY(){return getState().getProperty(Parameters::posYProp);}
int Astro::getCentreX(){return getState().getProperty(Parameters::posCentreXProp);}
int Astro::getCentreY(){return getState().getProperty(Parameters::posCentreYProp);}

float Astro::getDistance(const int xa, const int ya, const int xb, const int yb){
    float a = (float)pow(xb - xa, 2);
    float b = (float)pow(yb - ya, 2); 
    return sqrt(a + b);
}

float Astro::getDistance(Astro* astro_a, Astro* astro_b){
    int centreXA = astro_a->getCentreX();
    int centreYA = astro_a->getCentreY();
    int centreXB = astro_b->getCentreX();
    int centreYB = astro_b->getCentreY();

    float a = (float)pow(centreXB - centreXA, 2);
    float b = (float)pow(centreYB - centreYA, 2);

    return sqrt(a + b);
}

int Astro::getClipBoundary(){return Variables::CLIP_BOUNDARY;}

void Astro::generateSample(){getState().setProperty(Parameters::generateSampleSignal, true, nullptr);}

void Astro::playSample(){
    m_ParametersRef.setActivePlanet(getState());
    m_AudioContainerRef.m_SampleIndex.clear();
    m_AudioContainerRef.m_PlayAudio = true;
}

//--------------------------------------------------//
// Controller methods.

bool Astro::hitTest(const int x, const int y){
    float a = pow((float)x - (float)getRadiusWithClipBoundary(), 2.0f);
    float b = pow((float)y - (float)getRadiusWithClipBoundary(), 2.0f);
    return sqrt(a + b) <= getRadius();
}

void Astro::mouseEnter(const juce::MouseEvent& e){
    juce::ignoreUnused(e);

    m_ShowForceVectors = true;
    m_ControlPanelRef.show(getState(), this);

    getParentComponent()->repaint();
}

void Astro::mouseExit(const juce::MouseEvent& e){
    juce::ignoreUnused(e);

    m_ShowForceVectors = false;
    m_ControlPanelRef.unshow();
}

void Astro::valueChanged(juce::Value& value){
    juce::ignoreUnused(value);
    repaint();
}

//--------------------------------------------------//
// Animator class.

//--------------------------------------------------//
// Constructors and destructors.

Astro::Animator::Animator(){
    m_AreaShift = 0.0f;
    startTimer(Variables::ANIMATION_INTERVAL);
}

Astro::Animator::~Animator(){
    stopTimer();
}

//--------------------------------------------------//
// Interface methods.

float Astro::Animator::applyAreaShift(float area){return area + (float)m_AreaShift.getValue();}

float Astro::Animator::getDiameterShift(float area){
    float diameter = sqrt(area / Variables::PI) * 2.0f;
    float new_diameter = sqrt(applyAreaShift(area) / Variables::PI) * 2.0f;
    return new_diameter - diameter;
}

float Astro::Animator::getCreationDiameter(){
    return sqrt(m_AnimateCreation / Variables::PI) * 2.0f;
}

float Astro::Animator::getCreationRadius(){
    return getCreationDiameter() / 2.0f;
}

void Astro::Animator::animateCreation(){
    m_AnimateCreation += Variables::CREATION_AREA_SHIFT;
    if(m_AnimateCreation >= Variables::DEFAULT_PLANET_AREA)
        m_IsCreated = true;
}

void Astro::Animator::animate(){
    m_AreaShift = sin(m_Degrees) * Variables::AREA_SHIFT_LIMIT;

    if(m_Degrees >= 360.0f)
        m_Degrees = 0.0f;
    m_Degrees += 0.1f;
    
}

//--------------------------------------------------//
// Callback methods.

void Astro::Animator::timerCallback(){
    // TODO:
    // Fix the way this updates the component.

    if(!m_IsCreated)
        animateCreation();
    animate();
}

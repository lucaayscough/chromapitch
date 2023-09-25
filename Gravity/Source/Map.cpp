#include "Headers.h"


//--------------------------------------------------//
// Constructors and destructors.

Map::Map(AudioContainer& audiocontainer, Parameters& parameters, const juce::String& id)
    :   m_AudioContainerRef(audiocontainer), m_ParametersRef(parameters), m_ControlPanel(m_ParametersRef),
        m_Sun(m_AudioContainerRef, m_ParametersRef, m_ControlPanel){
    setComponentID(id);
    m_UpdateImage = false;

    setComponents();
    setGradients();
    addListeners();
}

Map::~Map(){
    removeListeners();
}

void Map::setComponents(){
    addChildComponent(m_ControlPanel, -1);
    addAndMakeVisible(m_Sun);
}

void Map::setGradients(){
    m_ForceVectorGradient.addColour((double)0.0, juce::Colours::darkred);
    m_ForceVectorGradient.addColour((double)0.2, juce::Colours::red);
    m_ForceVectorGradient.addColour((double)0.4, juce::Colours::orange);
    m_ForceVectorGradient.addColour((double)0.7, juce::Colours::yellow);
    m_ForceVectorGradient.addColour((double)1.0, juce::Colours::white);
}

void Map::addListeners(){
    m_ParametersRef.m_RootNode.addListener(this);
    m_ParametersRef.m_UpdateMap.addListener(this);
}

void Map::removeListeners(){
    m_ParametersRef.m_RootNode.removeListener(this);
    m_ParametersRef.m_UpdateMap.removeListener(this);
}

//--------------------------------------------------//
// View methods.

void Map::paint(juce::Graphics& g){
    int rect_overlap = 25;

    g.setColour(Variables::MAP_BG_COLOUR);
    g.fillRect(0, 0, getWidth(), getHeight() / 2);
    g.fillRoundedRectangle(0, getHeight() / 2 - rect_overlap, getWidth(), getHeight() / 2 + rect_overlap, 5.0f);

    // TODO:
    // This causes program to lock up on windows.
    
    paintOrbits(g);
    paintForceVectors(g);
    updateImage();
}

void Map::paintOrbits(juce::Graphics& g){
    auto rootPlanetNode = getRootPlanetNode();
    auto sunNode = getSunNode();

    for(int i = 0; i < rootPlanetNode.getNumChildren(); i++){
        g.setColour(Variables::MAP_CIRCLE_COLOUR);
        g.drawEllipse(
            (getWidth() / 2) - (m_ParametersRef.getDistance(rootPlanetNode.getChild(i), sunNode)), 
            (getHeight() / 2) - (m_ParametersRef.getDistance(rootPlanetNode.getChild(i), sunNode) ),
            m_ParametersRef.getDistance(rootPlanetNode.getChild(i), sunNode) * 2,
            m_ParametersRef.getDistance(rootPlanetNode.getChild(i), sunNode) * 2,
            1
        );
    }
}

void Map::paintForceVectors(juce::Graphics& g){
    // Draw planet vectors.
    for(Planet* planet_a : m_Planets){
        if((bool)planet_a->m_ShowForceVectors.getValue() == true){
            auto planet_node_a = getRootPlanetNode().getChildWithProperty(Parameters::idProp, planet_a->getComponentID());

            for(Planet* planet_b : m_Planets){
                if(planet_a->getComponentID() == planet_b->getComponentID()){
                    continue;
                }

                auto planet_node_b = getRootPlanetNode().getChildWithProperty(Parameters::idProp, planet_b->getComponentID());
                float force_vector = m_ParametersRef.getWeightedForceVector(planet_node_a, planet_node_b);
                drawForceVector(*planet_a, *planet_b, force_vector, g);
            }

            float force_vector = m_ParametersRef.getWeightedForceVector(getSunNode(), planet_node_a);
            drawForceVector(*planet_a, m_Sun, force_vector, g);
        }
    }

    // Draw sun vectors.
    if((bool)m_Sun.m_ShowForceVectors.getValue() == true){
        for(Planet* planet : m_Planets){
            auto planet_node = getRootPlanetNode().getChildWithProperty(Parameters::idProp, planet->getComponentID());
            auto force_vector = m_ParametersRef.getWeightedForceVector(getSunNode(), planet_node);
            drawForceVector(*planet, m_Sun, force_vector, g);
        }
    }
}

void Map::drawForceVector(Astro& astro_a, Astro& astro_b, float force_vector, juce::Graphics& g){
    g.setColour(juce::Colours::white);

    juce::Logger::writeToLog(std::to_string(force_vector));
    //g.setOpacity(force_vector);
    g.drawLine(astro_a.getCentreX(), astro_a.getCentreY(), astro_b.getCentreX(), astro_b.getCentreY(), Variables::FORCE_VECTOR_SIZE);
}

void Map::resized(){
    drawSun();

    if(m_Planets.size() < getNumPlanets())
        rebuildPlanets();

    m_ControlPanel.setBounds(getLocalBounds());
}

void Map::drawSun(){
    m_Sun.draw();
}

void Map::createPlanet(int x, int y){
    // TODO:
    // Add check for other astri.

    // Check creation position.
    int default_radius = Variables::getDefaultPlanetRadius();

    if(x - default_radius < 0)
        x = x + abs(x - default_radius);
    else if(x + default_radius > getWidth())
        x = x - ((x + default_radius) - getWidth());
    
    if(y - default_radius < 0)
        y = y + abs(y - default_radius);
    else if(y + default_radius > getHeight())
        y = y - ((y + default_radius) - getHeight());

    // Create planet node.
    m_ParametersRef.addPlanetNode(
        getComponentID(),
        x - Variables::getDefaultPlanetRadiusWithClipBoundary(),
        y - Variables::getDefaultPlanetRadiusWithClipBoundary()
    );
    juce::ValueTree planet = getRootPlanetNode().getChild(getRootPlanetNode().getNumChildren() - 1);

    // Set planet component.
    setPlanet(planet);
    m_ParametersRef.mixLatents(getMapNode());
}

void Map::setPlanet(juce::ValueTree node){
    juce::String id = node.getProperty(Parameters::idProp);
    m_Planets.add(new Planet(id, m_Planets, m_AudioContainerRef, m_ParametersRef, m_ControlPanel));

    Planet& planet = *m_Planets[m_Planets.size() - 1];
    addAndMakeVisible(planet);

    planet.draw();
}

void Map::rebuildPlanets(){
    for(int i = 0; i < getNumPlanets(); i++){
        // Create planet node.
        juce::ValueTree planet = getRootPlanetNode().getChild(i);
        juce::String id = planet.getProperty(Parameters::idProp);

        // Set planet component.
        setPlanet(planet);
    }

    m_ParametersRef.mixLatents(getMapNode());
}

void Map::destroyPlanet(juce::String& id){
    for(int i = 0; i < m_Planets.size(); i++){
        if(m_Planets[i]->getComponentID() == id){
            m_Planets.remove(i, true);
            m_ControlPanel.unshow();
            m_ParametersRef.mixLatents(getMapNode());
        }
    }
}

//--------------------------------------------------//
// Interface methods.

int Map::getMaxNumPlanets(){return Variables::MAX_NUM_PLANETS;}
int Map::getNumPlanets(){return getRootPlanetNode().getNumChildren();}
juce::ValueTree Map::getMapNode(){return m_ParametersRef.getMapNode(getComponentID());}
juce::ValueTree Map::getSunNode(){return m_ParametersRef.getSunNode(m_ParametersRef.getMapNode(getComponentID()));}
juce::ValueTree Map::getRootPlanetNode(){return m_ParametersRef.getRootPlanetNode(m_ParametersRef.getMapNode(getComponentID()));}

//--------------------------------------------------//
// Controller methods.

void Map::mouseUp(const juce::MouseEvent& e){juce::ignoreUnused(e);}

void Map::mouseDoubleClick(const juce::MouseEvent& e){
    if(e.mods.isLeftButtonDown()){
        int eventX = e.getMouseDownX();
        int eventY = e.getMouseDownY();

        if(getNumPlanets() < getMaxNumPlanets()){
            createPlanet(eventX, eventY);
        }
    }
}

//--------------------------------------------------//
// Callback methods.

void Map::valueChanged(juce::Value& value){
    juce::ignoreUnused(value);
    
    if(m_Planets.size() < getNumPlanets())
        rebuildPlanets();
    
    repaint();
}

void Map::valueTreePropertyChanged(juce::ValueTree& node, const juce::Identifier& id){
    juce::ignoreUnused(node);

    if(id == Parameters::isActiveProp){
        repaint();
    }
    if(id == Parameters::posXProp || id == Parameters::posYProp){
        repaint();
    }
}

void Map::valueTreeChildRemoved(juce::ValueTree& parentNode, juce::ValueTree& removedNode, int index){
    juce::ignoreUnused(parentNode, index);

    if(removedNode.getType() == Parameters::planetType){
        juce::String id = removedNode.getProperty(Parameters::idProp).toString();
        destroyPlanet(id);
        repaint();
    }
}

void Map::updateImage(){
    m_UpdateImage = true;
}

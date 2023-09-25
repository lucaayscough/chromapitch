#include "Headers.h"


//------------------------------------------------------------//
// Constructors and destructors.

Parameters::Parameters(juce::ValueTree v)
    :   m_RootNode(v){
    // Listeners.
    m_RootNode.addListener(this);
    m_UpdateMap = false;

    addMapNodes();
}

Parameters::~Parameters(){
    m_RootNode.removeListener(this);
}

//------------------------------------------------------------//
// Structuring methods.

void Parameters::addMapNodes(){
    for(int i = 0; i < Variables::NUM_MAPS; i++){
        // Create map node.
        juce::ValueTree mapNode(mapType);
        mapNode.setProperty(idProp, juce::String(i), nullptr);
        mapNode.setProperty(forceVectorSumProp, 1.0f, nullptr);

        bool isActive;
        if(i == 0) isActive = true;
        else isActive = false;
        
        mapNode.setProperty(isActiveProp, isActive, nullptr);

        // Create sun node.
        addSunNode(mapNode);

        // Create root node for planets.
        juce::ValueTree rootPlanetNode(rootPlanetType);
        mapNode.addChild(rootPlanetNode, -1, nullptr);

        // Attach map to root node.
        m_RootNode.addChild(mapNode, -1, nullptr);
    }
}

void Parameters::addSunNode(juce::ValueTree mapNode){
    // Create sun node.
    juce::ValueTree sunNode(sunType);
    sunNode.setProperty(areaProp, Variables::SUN_AREA, nullptr);
    sunNode.setProperty(idProp, M_SUN_ID, nullptr);

    // Listeners.
    sunNode.setProperty(generateSampleSignal, false, nullptr);

    // Sample.
    generateNewSample(sunNode);
    mapNode.addChild(sunNode, -1, nullptr);
    setActivePlanet(sunNode);
}

void Parameters::addPlanetNode(const juce::String& id, const int x, const int y){
    // Create planet node.
    juce::ValueTree planetNode(planetType);
    setRandomID(planetNode);
    planetNode.setProperty(areaProp, Variables::DEFAULT_PLANET_AREA, nullptr);
    planetNode.setProperty(posXProp, x, nullptr);
    planetNode.setProperty(posYProp, y, nullptr);

    // Listeners.
    planetNode.setProperty(generateSampleSignal, false, nullptr);
    
    // Sample.
    generateNewSample(planetNode);
    getRootPlanetNode(getMapNode(id)).addChild(planetNode, -1, nullptr);
}

void Parameters::removePlanetNode(juce::ValueTree node){
    getRootPlanetNode(getMapNode(node)).removeChild(node, nullptr);
}

void Parameters::clearSamples(juce::ValueTree rootNode){
    // TODO:
    // Cleanup this function.

    for(int i = 0; i < Variables::NUM_MAPS; i++){
        auto map = rootNode.getChild(i);

        for(int j = 0; j < map.getChildWithName(rootPlanetType).getNumChildren(); j++){
            map.getChildWithName(rootPlanetType).getChild(j).removeProperty(latentsProp, nullptr);
            map.getChildWithName(rootPlanetType).getChild(j).removeProperty(lerpLatentsProp, nullptr);
            map.getChildWithName(rootPlanetType).getChild(j).removeProperty(sampleProp, nullptr);
        }
        
        map.getChildWithName(sunType).removeProperty(latentsProp, nullptr);
        map.getChildWithName(sunType).removeProperty(lerpLatentsProp, nullptr);
        map.getChildWithName(sunType).removeProperty(sampleProp, nullptr);
    }
}

void Parameters::rebuildSamples(){
    // TODO:
    // Cleanup this function.

    for(int i = 0; i < Variables::NUM_MAPS; i++){
        auto map = m_RootNode.getChild(i);

        for(int j = 0; j < getRootPlanetNode(map).getNumChildren(); j++){
            generateLatents(getRootPlanetNode(map).getChild(j));
            generateLerpLatents(getRootPlanetNode(map).getChild(j));
            generateSample(getRootPlanetNode(map).getChild(j), getLatents(getRootPlanetNode(map).getChild(j), latentsProp));
        }

        generateLatents(map.getChildWithName(sunType));
        generateLerpLatents(map.getChildWithName(sunType));
        generateSample(map.getChildWithName(sunType), getLatents(map.getChildWithName(sunType), latentsProp));
    }
}

//------------------------------------------------------------//
// Tensor operations.

void Parameters::generateLatents(juce::ValueTree node){
    ReferenceCountedTensor::Ptr latents = new ReferenceCountedTensor(m_Generator.generateLatents(getSeed(node)));
    node.setProperty(latentsProp, juce::var(latents), nullptr);
}

void Parameters::generateLerpLatents(juce::ValueTree node){
    ReferenceCountedTensor::Ptr lerpLatents = new ReferenceCountedTensor(getLatents(node, latentsProp));
    node.setProperty(lerpLatentsProp, juce::var(lerpLatents), nullptr);
}

void Parameters::generateSample(juce::ValueTree node, at::Tensor tensor){
    // TODO:
    // Make it take a reference.

    node.setProperty(sampleProp, m_Generator.generateSample(tensor), nullptr);
}

void Parameters::generateNewSample(juce::ValueTree node){
    setRandomSeed(node);
    generateLatents(node);
    generateLerpLatents(node);
    generateSample(node, getLatents(node, latentsProp));
}

void Parameters::mixLatents(juce::ValueTree mapNode){
    // TODO:
    // Write more efficient way of doing same operation.

    setForceVectorSum(mapNode);
    float forceVector;
    float forceVectorSum = getForceVectorSum(mapNode);
    auto sunNode = getSunNode(mapNode);
    auto rootPlanetNode = getRootPlanetNode(mapNode);

    generateLerpLatents(sunNode);

    for(int i = 0; i < rootPlanetNode.getNumChildren(); i++){
        auto planet_a = rootPlanetNode.getChild(i);
        generateLerpLatents(planet_a);

        for(int j = 0; j < rootPlanetNode.getNumChildren(); j++){
            // TODO:
            // try fast matrix multiplication.

            if(i == j){continue;}

            auto planet_b = rootPlanetNode.getChild(j);
            if(getID(planet_a) == getID(planet_b)){continue;}

            forceVector = getForceVector(planet_a, planet_b) / forceVectorSum;
            juce::Logger::writeToLog(std::to_string(forceVector));
            at::Tensor newLatents = at::lerp(getLatents(planet_a, lerpLatentsProp), getLatents(planet_b, latentsProp), forceVector);
            setLatents(planet_a, lerpLatentsProp, newLatents);
        }
    }   

    for(int i = 0; i < rootPlanetNode.getNumChildren(); i++){
        auto planet = rootPlanetNode.getChild(i);

        forceVector = getForceVector(sunNode, planet) / forceVectorSum;
        juce::Logger::writeToLog(std::to_string(forceVector));
        at::Tensor newLatents = at::lerp(getLatents(sunNode, lerpLatentsProp), getLatents(planet, lerpLatentsProp), forceVector);
        setLatents(sunNode, lerpLatentsProp, newLatents);
    }

    generateSample(sunNode, getLatents(sunNode, lerpLatentsProp));
}

//------------------------------------------------------------//
// Interface methods.

juce::ValueTree Parameters::getActivePlanet(const juce::String& id){
    auto mapNode = getMapNode(id);
    auto rootPlanetNode = getRootPlanetNode(mapNode);

    for(int i = 0; i < rootPlanetNode.getNumChildren(); i++){
        if(rootPlanetNode.getChild(i).getProperty(isActiveProp)){
            return rootPlanetNode.getChild(i);
        }
    }
    
    return getSunNode(mapNode);
}

juce::ValueTree Parameters::getMapNode(const juce::String& id){return m_RootNode.getChild(id.getIntValue());}

juce::ValueTree Parameters::getMapNode(juce::ValueTree node){
    if(node.getParent().getParent().hasType(mapType)){
        return node.getParent().getParent();
    }
    else{
        return node.getParent();
    } 
}

juce::ValueTree Parameters::getSunNode(juce::ValueTree mapNode){return mapNode.getChildWithName(sunType);}
juce::ValueTree Parameters::getRootPlanetNode(juce::ValueTree mapNode){return mapNode.getChildWithName(rootPlanetType);}
std::int64_t Parameters::getSeed(juce::ValueTree node){return node.getProperty(seedProp);}
at::Tensor Parameters::getLatents(juce::ValueTree node, juce::Identifier& id){return ((ReferenceCountedTensor*)node.getProperty(id).getObject())->getTensor();}
juce::String Parameters::getID(juce::ValueTree node){return node.getProperty(idProp);}

float Parameters::getDistance(juce::ValueTree node_a, juce::ValueTree node_b){  
    int centreXA = node_a.getProperty(posCentreXProp);
    int centreYA = node_a.getProperty(posCentreYProp);
    int centreXB = node_b.getProperty(posCentreXProp);
    int centreYB = node_b.getProperty(posCentreYProp);

    float a = (float)pow(centreXB - centreXA, 2.0f);
    float b = (float)pow(centreYB - centreYA, 2.0f);

    return sqrt(a + b);
}

float Parameters::getForceVector(juce::ValueTree node_a, juce::ValueTree node_b){
    // TODO:
    // Calculate with respect to the sum of the vectors.

    float mass_a, mass_b;

    if(node_a.getType() == sunType){
        mass_a = (float)node_a.getProperty(areaProp);
    }
    else{
        mass_a = (float)node_a.getProperty(areaProp);
    }

    if(node_b.getType() == sunType){
        mass_b = (float)node_b.getProperty(areaProp);
    }
    else{
        mass_b = (float)node_b.getProperty(areaProp);
    }

    float m = mass_a * mass_b;
    float r = getDistance(node_a, node_b);

    float result = m / (r * r);

    return result;
}

float Parameters::getForceVectorSum(juce::ValueTree mapNode){
    return mapNode.getProperty(forceVectorSumProp);
}

float Parameters::getWeightedForceVector(juce::ValueTree node_a, juce::ValueTree node_b){
    float forceVector = getForceVector(node_a, node_b);
    float vectorSum = getForceVectorSum(getMapNode(node_a));
    return forceVector / vectorSum;
}

void Parameters::setActivePlanet(juce::ValueTree node){
    auto mapNode = getMapNode(node);

    for(int i = 0; i < getRootPlanetNode(mapNode).getNumChildren(); i++){
        getRootPlanetNode(mapNode).getChild(i).setProperty(isActiveProp, false, nullptr);
    }
    
    getSunNode(mapNode).setProperty(isActiveProp, false, nullptr);
    node.setProperty(isActiveProp, true, nullptr);
}

void Parameters::setRandomID(juce::ValueTree node){
    auto rootPlanetNode = getRootPlanetNode(getMapNode(node));

    // Generate random ID for component.
    auto randomID = juce::String(juce::Random::getSystemRandom().nextInt(1000));    

    // Check if ID is unique.
    for(int i = 0; i < rootPlanetNode.getNumChildren() - 1; i++){
        if(rootPlanetNode.getChild(i).getProperty(idProp) == randomID){
            while(rootPlanetNode.getChild(i).getProperty(idProp) == randomID){
                randomID = juce::String(juce::Random::getSystemRandom().nextInt(1000)); 
            }
        }
    }

    // Set ID.
    node.setProperty(idProp, randomID, nullptr);
}

void Parameters::setRandomSeed(juce::ValueTree node){
    std::int64_t seed = juce::Random::getSystemRandom().nextInt64();
    if(seed < 0){seed = seed * -1;}
    node.setProperty(seedProp, seed, nullptr);
}

void Parameters::setLatents(juce::ValueTree node, juce::Identifier& id, at::Tensor& latents){
    ReferenceCountedTensor::Ptr lerpLatents = new ReferenceCountedTensor(latents);
    node.setProperty(lerpLatentsProp, juce::var(lerpLatents), nullptr);
    node.setProperty(id, juce::var(lerpLatents), nullptr);
}

void Parameters::setForceVectorSum(juce::ValueTree mapNode){
    float forceVectorSum;
    auto sunNode = getSunNode(mapNode);
    auto rootPlanetNode = getRootPlanetNode(mapNode);

    for(int i = 0; i < rootPlanetNode.getNumChildren(); i++){
        auto planet_a = rootPlanetNode.getChild(i);

        for(int j = 0; j < rootPlanetNode.getNumChildren(); j++){
            // TODO:
            // try fast matrix multiplication.

            if(i == j)
                continue;

            auto planet_b = rootPlanetNode.getChild(j);

            if(getID(planet_a) == getID(planet_b))
                continue;

            forceVectorSum += getForceVector(planet_a, planet_b);
        }
    }

    for(int i = 0; i < rootPlanetNode.getNumChildren(); i++){
        auto planet = rootPlanetNode.getChild(i);
        forceVectorSum += getForceVector(sunNode, planet);
    }

    mapNode.setProperty(forceVectorSumProp, forceVectorSum, nullptr);
}

//------------------------------------------------------------//
// Callback methods.

void Parameters::sendMapUpdate(){
    m_UpdateMap = true;
    m_UpdateMap = false;
}

void Parameters::valueTreePropertyChanged(juce::ValueTree& node, const juce::Identifier& id){
    if(id == generateSampleSignal){
        if((bool)node.getProperty(id) == true){
            generateNewSample(node);
            node.setProperty(id, false, nullptr);
        }
    }
}

//------------------------------------------------------------//
// Member variables.

juce::String Parameters::M_SUN_ID("Sun");

//------------------------------------------------------------//
// Type identifiers.

juce::Identifier Parameters::mapType("Map");
juce::Identifier Parameters::sunType("Sun");
juce::Identifier Parameters::rootPlanetType("Root_Planet");
juce::Identifier Parameters::planetType("Planet");

//------------------------------------------------------------//
// Property identifiers.

juce::Identifier Parameters::idProp("ID");
juce::Identifier Parameters::isActiveProp("Is_Active");
juce::Identifier Parameters::areaProp("Area");
juce::Identifier Parameters::posXProp("Position_X");
juce::Identifier Parameters::posYProp("Position_Y");
juce::Identifier Parameters::posCentreXProp("Position_Centre_X");
juce::Identifier Parameters::posCentreYProp("Position_Centre_Y");
juce::Identifier Parameters::colourProp("Colour");
juce::Identifier Parameters::seedProp("Seed");
juce::Identifier Parameters::latentsProp("Latents");
juce::Identifier Parameters::lerpLatentsProp("Interpolated_Latents");
juce::Identifier Parameters::sampleProp("Sample");
juce::Identifier Parameters::forceVectorSumProp("Force_Vector_Sum");

//------------------------------------------------------------//
// Callback signalers.

juce::Identifier Parameters::generateSampleSignal("Generate_Sample");

//------------------------------------------------------------//
// Threads.

Parameters::MixerThread::MixerThread()
    :   Thread("Mixer Thread"){}

Parameters::MixerThread::~MixerThread(){}

void Parameters::MixerThread::run(){}


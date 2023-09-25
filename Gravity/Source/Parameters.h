#pragma once


struct Parameters: public juce::ValueTree::Listener{
    // Constructors and destructors.
    Parameters(juce::ValueTree);
    ~Parameters() override;

    // Restructuring methods.
    void addMapNodes();
    void addSunNode(juce::ValueTree);
    void addPlanetNode(const juce::String&, const int x, const int y);
    void removePlanetNode(juce::ValueTree);
    void clearSamples(juce::ValueTree);
    void rebuildSamples();

    // Tensor operations.
    void generateLatents(juce::ValueTree);
    void generateLerpLatents(juce::ValueTree);
    void generateSample(juce::ValueTree, at::Tensor);
    void generateOldSample(juce::ValueTree);
    void generateNewSample(juce::ValueTree);
    void mixLatents(juce::ValueTree);

    // Interface methods.
    juce::ValueTree getMapNode(const juce::String&);
    juce::ValueTree getMapNode(juce::ValueTree);
    juce::ValueTree getSunNode(juce::ValueTree);
    juce::ValueTree getRootPlanetNode(juce::ValueTree);
    std::int64_t getSeed(juce::ValueTree);
    at::Tensor getLatents(juce::ValueTree, juce::Identifier&);
    juce::ValueTree getActivePlanet(const juce::String&);
    juce::String getID(juce::ValueTree);
    float getDistance(juce::ValueTree, juce::ValueTree);
    float getForceVector(juce::ValueTree, juce::ValueTree);
    float getForceVectorSum(juce::ValueTree);
    float getWeightedForceVector(juce::ValueTree, juce::ValueTree);

    void setActivePlanet(juce::ValueTree);
    void setRandomID(juce::ValueTree);
    void setRandomSeed(juce::ValueTree);
    void setLatents(juce::ValueTree, juce::Identifier&, at::Tensor&);
    void setForceVectorSum(juce::ValueTree);

    // Callback methods.
    void sendMapUpdate();
    void valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&) override;

    // Member variables.
    juce::ValueTree m_RootNode;
    bool m_IsInit = false;
    juce::Value m_UpdateMap;
    static juce::String M_SUN_ID;
    Generator m_Generator;

    // Type identifiers.
    static juce::Identifier mapType;
    static juce::Identifier sunType;
    static juce::Identifier rootPlanetType;
    static juce::Identifier planetType;

    // Property identifiers.
    static juce::Identifier idProp;
    static juce::Identifier isActiveProp;
    static juce::Identifier areaProp;
    static juce::Identifier posXProp;
    static juce::Identifier posYProp;
    static juce::Identifier posCentreXProp;
    static juce::Identifier posCentreYProp;
    static juce::Identifier colourProp;
    static juce::Identifier seedProp;
    static juce::Identifier latentsProp;
    static juce::Identifier lerpLatentsProp;
    static juce::Identifier sampleProp;
    static juce::Identifier forceVectorSumProp;

    // Callback signalers.
    static juce::Identifier generateSampleSignal;

    // Threads.
    struct MixerThread: public juce::Thread{
        MixerThread();
        ~MixerThread() override;
        void run() override;
    };

    MixerThread mixerThread;
};

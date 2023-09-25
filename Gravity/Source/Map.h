#pragma once


class Map: public juce::Component, public juce::Value::Listener, juce::ValueTree::Listener{
public:
    // Constructors and destructors.
    Map(AudioContainer&, Parameters&, const juce::String&);
    ~Map() override;

    void setComponents();
    void addListeners();
    void setGradients();
    void removeListeners();

private:
    // View methods.
    void paint(juce::Graphics&) override;
    void paintOrbits(juce::Graphics&);
    void paintForceVectors(juce::Graphics&);
    void drawForceVector(Astro&, Astro&, float, juce::Graphics&);
    void resized() override;
    
    void drawSun();
    void createPlanet(int, int);
    void setPlanet(juce::ValueTree);
    void rebuildPlanets();
    void destroyPlanet(juce::String&);

    // Interface methods
    int getMaxNumPlanets();
    int getNumPlanets();
    juce::ValueTree getMapNode();
    juce::ValueTree getSunNode();
    juce::ValueTree getRootPlanetNode();

    // Controller methods.
    void mouseUp(const juce::MouseEvent&) override;
    void mouseDoubleClick(const juce::MouseEvent&) override;

    // Callback methods.
    void valueChanged(juce::Value&) override;
    void valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&) override;
    void valueTreeChildRemoved(juce::ValueTree&, juce::ValueTree&, int) override;
    void updateImage();

public:
    // Member variables.
    juce::Value m_UpdateImage;

private:
    // Member variables.
    juce::OwnedArray<Planet> m_Planets;
    AudioContainer& m_AudioContainerRef;
    Parameters& m_ParametersRef;
    ControlPanel m_ControlPanel;
    Sun m_Sun;
    juce::ColourGradient m_ForceVectorGradient;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Map)
};

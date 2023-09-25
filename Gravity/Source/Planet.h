#pragma once


class Planet: public Astro{
public: 
    // Constructors and destructors.
    Planet(juce::String&, juce::OwnedArray<Planet>&, AudioContainer&, Parameters&, ControlPanel&);
    ~Planet() override;

public:
    // View methods.
    void resized() override;
    void resizePlanet(float);
    void checkCollision();
    void checkBounds();

public:
    // Interface methods.
    juce::ValueTree getState() override;

private:
    // Controller methods.
    void mouseDown(const juce::MouseEvent&) override;
    void mouseUp(const juce::MouseEvent&) override;
    void mouseDrag(const juce::MouseEvent&) override;
    void mouseWheelMove(const juce::MouseEvent&, const juce::MouseWheelDetails&) override;

private:
    // Member variables.
    juce::ComponentDragger m_Dragger;
    juce::OwnedArray<Planet>& m_PlanetsRef;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Planet)
};



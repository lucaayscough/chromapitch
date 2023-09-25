#pragma once


class ControlPanel: public juce::Component{
public:
    // Constructors and destructors.
    ControlPanel(Parameters&);
    ~ControlPanel() override;

public:
    // View methods.
    void show(juce::ValueTree, juce::Component*);
    void unshow();

private:
    // View methods.
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // Control methods.
    void visibilityChanged() override;
    bool hitTest(int x, int y) override;

private:
    // Member variables.
    Parameters& m_ParametersRef;

    float m_Width = 100;
    float m_Height = 60;

    juce::ValueTree m_State;
    juce::Component* m_Component;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlPanel)
};

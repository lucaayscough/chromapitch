#pragma once


class LeftBar: public juce::Component{
public:
    // Constructors and destructors.
    LeftBar(juce::OwnedArray<Map>&);
    ~LeftBar() override;

private:
    // View methods.
    void paint(juce::Graphics&) override;
    void resized() override;

public:
    // Interface methods.
    void setListeners();

public:
    juce::OwnedArray<Map>& m_MapsRef;
    juce::OwnedArray<MapButton> m_MapButtons;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LeftBar)
};

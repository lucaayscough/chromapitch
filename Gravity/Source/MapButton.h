#pragma once


class MapButton: public juce::Component, public juce::Value::Listener{
public:
    // Constructors and destructors.
    MapButton(juce::OwnedArray<Map>&, const juce::String&);
    ~MapButton() override;

public:
    // Init methods.
    void setListeners();

private:
    // View methods.
    void paint(juce::Graphics&) override;
    void resized() override;

public:
    // Interface methods.
    int getButtonIndex();
    Map& getMap();
    void setImage();

private:
    // Controller methods.
    void mouseDown(const juce::MouseEvent&) override;

private:
    // Callback methods.
    void valueChanged(juce::Value&) override;

private:
    // Member variables.
    juce::OwnedArray<Map>& m_MapsRef;
    juce::ImageComponent m_MapImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MapButton)
};

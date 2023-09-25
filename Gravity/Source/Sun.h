#pragma once


class Sun: public Astro{
public:
    // Constructors and destructors.
    Sun(AudioContainer&, Parameters&, ControlPanel&);
    ~Sun() override;

public:
    // View methods.
    void resized() override;
    void draw() override;

public:
    // Interface methods.
    juce::ValueTree getState() override;

private:
    // Controller methods.
    void mouseDown(const juce::MouseEvent& e) override;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Sun)
};

#pragma once


class NoteBox : public juce::Component
{
public:
    NoteBox();
    ~NoteBox();

    void turnOn();
    void turnOff();
    void setGradientPos(float gradientPos);
    void update();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::ColourGradient m_gradient;
    bool m_isOn = false;
    float m_gradientPos = 0.5f;
    float m_alpha = 0.f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(NoteBox)
};

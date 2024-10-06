#pragma once


class Header : public juce::Component
{
public:
    Header();
    ~Header();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::ImageComponent m_Logo;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Header)
};

#pragma once


class Header : public juce::Component
{
public:
    Header();
    ~Header();

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Header)
};

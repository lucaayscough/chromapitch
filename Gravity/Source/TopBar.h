#pragma once


class TopBar: public juce::Component{
public:
    // Constructors and destructors.
    TopBar();
    ~TopBar() override;

private:
    // View methods.
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // Member variables.
    juce::ImageComponent m_LogoImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TopBar)
};

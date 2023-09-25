#pragma once


class Astro: public juce::Component, public juce::Value::Listener{
public: 
    // Constructors and destructors.
    Astro(juce::String&, AudioContainer&, Parameters&, ControlPanel&);
    ~Astro() override;

public:
    // Init methods.
    virtual void setListeners();
    virtual void setGradients();

public:
    // View methods.
    void paint(juce::Graphics&) override;
    virtual void paintCircle(float, float, juce::Graphics&);
    virtual void draw();
    virtual void draw(const int, const int, const int);

public:
    // Interface methods.
    virtual void setArea(const float);
    virtual void setPosXY(const int, int);
    virtual void setCentrePosXY(const int, const int);

    virtual juce::ValueTree getState() = 0;
    virtual juce::ValueTree getMapNode();
    virtual float getArea();
    virtual int getDiameter();
    virtual int getDiameterWithClipBoundary();
    virtual int getRadius();
    virtual int getRadiusWithClipBoundary();
    virtual int getPosX();
    virtual int getPosY();
    virtual int getCentreX();
    virtual int getCentreY();
    virtual int getClipBoundary();

    virtual float getDistance(const int, const int, const int, const int);
    virtual float getDistance(Astro*, Astro*);

    virtual void generateSample();

    virtual void playSample();

protected:
    // Controller methods.
    bool hitTest(const int, const int) override;
    void mouseEnter(const juce::MouseEvent&) override;
    void mouseExit(const juce::MouseEvent&) override;
    void valueChanged(juce::Value&) override;

protected:
    // Member variables.
    AudioContainer& m_AudioContainerRef;
    Parameters& m_ParametersRef;
    ControlPanel& m_ControlPanelRef;

    juce::ColourGradient m_ColourGradient;

public:
    // Member variables.
    juce::Value m_ShowForceVectors;

public:
    // Animator class.
    class Animator: juce::Timer{
    public:
        // Constructors and destructors.
        Animator();
        ~Animator() override;

        // Interface methods.
        float applyAreaShift(float);
        float getDiameterShift(float);

        float getCreationDiameter();
        float getCreationRadius();

        void animateCreation();
        void animate();

        // Callback methods.
        void timerCallback() override;

        // Member variables.
        juce::Value m_AreaShift;
        float m_Degrees = 0.0f;

        bool m_IsCreated = false;
        float m_AnimateCreation = 0.0f;
    };

protected:
    // Member variables.
    Animator m_Animator;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Astro)
};



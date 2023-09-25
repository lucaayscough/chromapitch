#pragma once


class AudioPluginAudioProcessor: public juce::AudioProcessor, juce::ValueTree::Listener{
public:
    // Constructors and destructors.
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    // Process methods.
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    // Editor methods.
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;

    // Midi methods.
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    // Program methods.
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    // State methods.
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    void rebuildState();

    // Callback methods.
    void valueTreePropertyChanged(juce::ValueTree&, const juce::Identifier&) override;

private:
    // Playback methods.
    void playAudio(juce::AudioBuffer<float>&, int, int);
    void stopAudio();
    void playSample();
    void addSample(juce::ValueTree);

public:
    // Member variables.
    AudioContainer m_AudioContainer;
    juce::AudioProcessorValueTreeState m_ValueTreeState;
    Parameters m_Parameters;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};

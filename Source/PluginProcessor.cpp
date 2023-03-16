#include "Headers.h"

//==============================================================================
ChromaPitchAudioProcessor::ChromaPitchAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{}

ChromaPitchAudioProcessor::~ChromaPitchAudioProcessor() {}

const juce::String ChromaPitchAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChromaPitchAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChromaPitchAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ChromaPitchAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ChromaPitchAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChromaPitchAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChromaPitchAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChromaPitchAudioProcessor::setCurrentProgram (int index) {}

const juce::String ChromaPitchAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChromaPitchAudioProcessor::changeProgramName (int index, const juce::String& newName) {}

//==============================================================================
void ChromaPitchAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    m_frequencyEstimator.prepareToPlay(sampleRate, Variables::minimumFrequency, Variables::maximumFrequency);
}

void ChromaPitchAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChromaPitchAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ChromaPitchAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    m_frequencyEstimator.processBlock(buffer);

    auto note = getLastNote();
    m_MPE.processBlock(midiMessages, note);
}

//==============================================================================
bool ChromaPitchAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* ChromaPitchAudioProcessor::createEditor()
{
    return new ChromaPitchAudioProcessorEditor (*this);
}

//==============================================================================
void ChromaPitchAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {}

void ChromaPitchAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChromaPitchAudioProcessor();
}

Chroma::NoteInfo ChromaPitchAudioProcessor::getLastNote()
{
    return m_frequencyEstimator.getLastNote();
}

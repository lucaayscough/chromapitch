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
{
}

ChromaPitchAudioProcessor::~ChromaPitchAudioProcessor()
{
}

//==============================================================================
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

void ChromaPitchAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ChromaPitchAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChromaPitchAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ChromaPitchAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    oscillator.prepareToPlay (440, sampleRate, samplesPerBlock);
}

void ChromaPitchAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

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

void ChromaPitchAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    buffer.clear();
    
    auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
    
    int numCrossings = 0;
    bool sign = false;
    
    oscillator.processBlock();
    auto block = oscillator.getBlock();
    
    buffer.addFrom(0, 0, block, 0, 0, numSamples);
    buffer.addFrom(1, 0, block, 0, 0, numSamples);

    // Detect pitch.
    for (int channel = 0; channel < 1; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            if (channelData[sample] > 0.f && sign == false)
            {
                sign = true;
                ++numCrossings;
            }
            
            else if (channelData[sample] < 0.f && sign == true)
            {
                sign = false;
                ++numCrossings;
            }
        }
    }
    
    float frequency = ((float)numCrossings / 2.f) * (getSampleRate() / (float)numSamples);
    
    DBG (frequency);
}

//==============================================================================
bool ChromaPitchAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ChromaPitchAudioProcessor::createEditor()
{
    return new ChromaPitchAudioProcessorEditor (*this);
}

//==============================================================================
void ChromaPitchAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void ChromaPitchAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChromaPitchAudioProcessor();
}

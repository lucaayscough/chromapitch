#include "Headers.h"


//------------------------------------------------------------//
// Constructors and destructors.

AudioPluginAudioProcessor::AudioPluginAudioProcessor()
    :   AudioProcessor(BusesProperties()
            #if ! JucePlugin_IsMidiEffect
                #if ! JucePlugin_IsSynth
                    .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                #endif
                .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
            #endif
        ),
        m_ValueTreeState(*this, nullptr, getName(), {}),
        m_Parameters(m_ValueTreeState.state){
    m_ValueTreeState.state.addListener(this);
}

AudioPluginAudioProcessor::~AudioPluginAudioProcessor(){}

//------------------------------------------------------------//
// Process methods.

void AudioPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock){
    juce::ignoreUnused (sampleRate, samplesPerBlock);
}

void AudioPluginAudioProcessor::releaseResources(){}
bool AudioPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    #if JucePlugin_IsMidiEffect
        juce::ignoreUnused (layouts);
        return true;
    #else

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

void AudioPluginAudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages){
    juce::ScopedNoDenormals noDenormals;
    int totalNumInputChannels  = getTotalNumInputChannels();
    int totalNumOutputChannels = getTotalNumOutputChannels();
    int numSamples = buffer.getNumSamples();

    while(m_AudioContainer.m_SampleIndex.size() <= totalNumOutputChannels){
        m_AudioContainer.m_SampleIndex.add(0);
    }
    
    // Clear extra channel buffers.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());

    // Check for midi data.
    for(const juce::MidiMessageMetadata metadata : midiMessages){
        juce::Logger::writeToLog(metadata.getMessage().getDescription());
        if(metadata.getMessage().isNoteOn())
            m_AudioContainer.m_PlayAudio = true;
        else if(metadata.getMessage().isNoteOff()){
            stopAudio();
        }
    }

    // Check for generic play request.
    if(m_AudioContainer.m_PlayAudio){
        playAudio(buffer, totalNumOutputChannels, numSamples);
    }
}

//------------------------------------------------------------//
// Editor methods.

const juce::String AudioPluginAudioProcessor::getName() const {return JucePlugin_Name;}
bool AudioPluginAudioProcessor::hasEditor() const{return true;}
juce::AudioProcessorEditor* AudioPluginAudioProcessor::createEditor(){return new AudioPluginAudioProcessorEditor (*this);}

//------------------------------------------------------------//
// Midi methods.

bool AudioPluginAudioProcessor::acceptsMidi() const{
    #if JucePlugin_WantsMidiInput
        return true;
    #else
        return false;
    #endif
}

bool AudioPluginAudioProcessor::producesMidi() const{
    #if JucePlugin_ProducesMidiOutput
        return true;
    #else
        return false;
    #endif
}

bool AudioPluginAudioProcessor::isMidiEffect() const{
    #if JucePlugin_IsMidiEffect
        return true;
    #else
        return false;
    #endif
}

double AudioPluginAudioProcessor::getTailLengthSeconds() const {return 0.0;}

//------------------------------------------------------------//
// Program methods.

int AudioPluginAudioProcessor::getNumPrograms(){return 1;}
int AudioPluginAudioProcessor::getCurrentProgram(){return 0;}
void AudioPluginAudioProcessor::setCurrentProgram (int index){juce::ignoreUnused (index);}

const juce::String AudioPluginAudioProcessor::getProgramName (int index){
    juce::ignoreUnused (index);
    return {};
}

void AudioPluginAudioProcessor::changeProgramName (int index, const juce::String& newName){juce::ignoreUnused (index, newName);}

//------------------------------------------------------------//
// State methods.

void AudioPluginAudioProcessor::getStateInformation(juce::MemoryBlock& destData){
    if(m_Parameters.m_IsInit){
        auto stateCopy = m_ValueTreeState.state.createCopy();
        m_Parameters.clearSamples(stateCopy);
        std::unique_ptr<juce::XmlElement> xml(stateCopy.createXml());
        copyXmlToBinary(*xml, destData);
    }
    else{m_Parameters.m_IsInit = true;}
}

void AudioPluginAudioProcessor::setStateInformation(const void* data, int sizeInBytes){
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState.get() != nullptr){
        if (xmlState->hasTagName(m_ValueTreeState.state.getType())){
            m_ValueTreeState.state.copyPropertiesAndChildrenFrom(juce::ValueTree::fromXml(*xmlState), nullptr);
            rebuildState();
        }
    }
}

void AudioPluginAudioProcessor::rebuildState(){
    m_Parameters.rebuildSamples();
    m_Parameters.sendMapUpdate();
}

//------------------------------------------------------------//
// Callback methods.

void AudioPluginAudioProcessor::valueTreePropertyChanged(juce::ValueTree& node, const juce::Identifier& id){
    if(id == Parameters::isActiveProp){
        if(node.getProperty(Parameters::isActiveProp)){
            addSample(node);
        }
    }

    if(id == Parameters::sampleProp){
        if(node.getProperty(Parameters::isActiveProp)){
            addSample(node);
        }
    }
}

//------------------------------------------------------------//
// Playback methods.

void AudioPluginAudioProcessor::playAudio(juce::AudioBuffer<float>& buffer, int totalNumOutputChannels, int numSamples){
    buffer.clear();
    
    for (int channel = 0; channel < totalNumOutputChannels; ++channel){
        auto* channelData = buffer.getWritePointer(channel);
        juce::ignoreUnused(channelData);
        
        for(int sample = 0; sample < numSamples; ++sample){
            // Add samples to buffer if max length of samples is not exceeded.
            if(m_AudioContainer.m_SampleIndex[channel] < AudioContainer::M_NUM_SAMPLES){
                channelData[sample] = m_AudioContainer.m_Audio[m_AudioContainer.m_SampleIndex[channel]];
                // TODO:
                // Something goes wrong here.
                m_AudioContainer.m_SampleIndex.set(channel, m_AudioContainer.m_SampleIndex[channel] + 1);
            }
            else{
                stopAudio();
            }
        }
    }
}

void AudioPluginAudioProcessor::stopAudio(){
    m_AudioContainer.m_SampleIndex.clear();
    m_AudioContainer.m_PlayAudio = false;
}

void AudioPluginAudioProcessor::playSample(){
    m_AudioContainer.m_SampleIndex.clear();
    m_AudioContainer.m_PlayAudio = true;
}

void AudioPluginAudioProcessor::addSample(juce::ValueTree node){
    m_AudioContainer.m_Audio.clear();

    juce::Array<float> sample;
    sample.ensureStorageAllocated(AudioContainer::M_NUM_SAMPLES);

    juce::Array<juce::var>* values = node.getProperty(Parameters::sampleProp).getArray();
    for(int i = 0; i < AudioContainer::M_NUM_SAMPLES; i++)
        sample.insert(i, (*values)[i]);

    m_AudioContainer.m_Audio.addArray(sample);
}

//------------------------------------------------------------//
// This creates new instances of the plugin.

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter(){return new AudioPluginAudioProcessor();}

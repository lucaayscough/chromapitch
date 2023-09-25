#include "Headers.h"


AudioContainer::AudioContainer(){
    m_AudioBuffers.ensureStorageAllocated(Variables::NUM_MAPS);
    
    for(int i = 0; i < Variables::NUM_MAPS; i++){
        m_AudioBuffers.add(new juce::AudioBuffer<float>(M_NUM_CHANNELS, M_NUM_SAMPLES));
    }
}

AudioContainer::~AudioContainer(){}

const int AudioContainer::M_NUM_SAMPLES = 131072;
const int AudioContainer::M_NUM_CHANNELS = 1;

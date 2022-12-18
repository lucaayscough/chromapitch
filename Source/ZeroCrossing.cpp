#include "Headers.h"


ZeroCrossing::ZeroCrossing() {}

ZeroCrossing::~ZeroCrossing() {}

void ZeroCrossing::prepareToPlay(double sampleRateToUse)
{
    sampleRate = sampleRateToUse;
}

void ZeroCrossing::getFrequency(juce::AudioBuffer<float>& buffer)
{
    //auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
    
    // Detect pitch.
    for (int channel = 0; channel < 1; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        double frequency = 0;
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            ++window;
            
            if (channelData[sample] >= 0 && sign == false)
            {
                ++numCrossings;
                sign = true;
            }
            
            else if (channelData[sample] < 0 && sign == true)
            {
                ++numCrossings;
                sign = false;
            }
            
            if (numCrossings == 2)
            {
                // TODO:
                // check this...
                
                double subSampleCrossing = 0.0;
                
                if (channelData[sample] != 0)
                {
                    subSampleCrossing = -channelData[sample - 1] / (channelData[sample - 1] - channelData[sample]);
                }
                
                window = window - subSampleCrossing;
                frequency = sampleRate / window;

                window = subSampleCrossing;
                numCrossings = 0;
                
                //DBG(subSampleCrossing);
                DBG (frequency);
            }
        }
    }

}

#include "Headers.h"


ZeroCrossing::ZeroCrossing() {}

ZeroCrossing::~ZeroCrossing() {}

double ZeroCrossing::getFrequency()
{
    return frequency;
}

bool ZeroCrossing::isReadingValid()
{
    return validReading;
}

void ZeroCrossing::prepareToPlay(double sampleRateToUse)
{
    sampleRate = sampleRateToUse;
}

void ZeroCrossing::computeFrequency(juce::AudioBuffer<float>& buffer)
{
    
    
    // TODO:
    // Make this stereo.
    
    //auto numChannels = buffer.getNumChannels();
    auto numSamples = buffer.getNumSamples();
    
    auto rms = buffer.getRMSLevel(0, 0, numSamples);
    auto db = juce::Decibels::gainToDecibels(rms);
    
    validReading = db > Variables::dbThreshold;
    
    if (!validReading)
    {
        return;
    }
    
    // Detect pitch.
    for (int channel = 0; channel < 1; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        for (int sample = 0; sample < numSamples; ++sample)
        {
            currentSample = channelData[sample];
            
            if (currentSample >= 0.0 && sign == false)
            {
                ++numCrossings;
                sign = true;
            }
            
            else if (currentSample <= 0.0 && sign == true)
            {
                ++numCrossings;
                sign = false;
            }
            
            if (numCrossings == 3)
            {
                double subSampleCrossing = 0.0;
                
                if (currentSample != 0.0)
                {
                    subSampleCrossing = - (previousSample / (currentSample - previousSample));
                }
                
                window = window - 1.0 + subSampleCrossing;
                frequency = sampleRate / window;
                DBG (frequency);

                // Prepare for next round.
                window = 1.0 - subSampleCrossing;
                numCrossings = 0;
                sign = false;
                sample -= 1;
            }
            
            else
            {
                ++window;
            }
            
            previousSample = currentSample;
        }
    }
}

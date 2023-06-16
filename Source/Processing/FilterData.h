/*
  ==============================================================================

    FilterData.h
    Created: 11 May 2023 10:04:44pm
    Author:  lisa liu

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*
 This class represents the data that our filter component collects based on the user's
 selected filtet type as well as their interactions with the sliders.
 */
class FilterData
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void process(juce::AudioBuffer<float>& buffer);
    void updateFilterParameters(const int filterType, const float frequency, const float resonance,
        const float modulator);
    void resetFilter();
private:
    juce::dsp::StateVariableTPTFilter <float> filter;
    bool isPrepared{ false };
};

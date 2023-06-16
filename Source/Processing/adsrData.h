

/*
  ==============================================================================

    adsrData.h
    Created: 5 May 2023 6:15:22pm
    Author:  Makayla McPherson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*
 This class represents the data collected by the ADSR/envelope component, which is based
 on the user's interactions with the sliders.
 */
class adsrData : public juce::ADSR // this line allows adsrData to inherit from juce::adsr
{
public:
    void updateADSR(const float attack, const float decay, const float sustain, const float release);
    
private:
    juce::ADSR::Parameters adsrParams;
};

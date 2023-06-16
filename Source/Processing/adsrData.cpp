/*
  ==============================================================================

    adsrData.cpp
    Created: 5 May 2023 6:15:22pm
    Author:  Makayla McPherson

  ==============================================================================
*/

#include "adsrData.h"

void adsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;
    
    setParameters(adsrParams);
    
}

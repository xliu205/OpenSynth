/*
  ==============================================================================

    SynthVoice.h
    Created: 28 Apr 2023 1:33:24pm
    Author:  Andy Truss

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Processing/FilterData.h"
#include "Processing/adsrData.h"
#include "Processing/OscData.h"


/*
 This class represents each of the voices our plugin can work with. Essentially, having
 multiple voices (a polyphonic synth) means that multiple notes on a MIDI keyboard can all
 be played at once.
 */
class SynthVoice : public juce::SynthesiserVoice {
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    

    void updateFilter(const int filterType, const float cutoff, const float resonance);
    FilterData& getFilter() { return filter; }
    adsrData& getFilterADSR() { return filterADSR;  }
    OscData& getOscillator1() { return osc1; }
    OscData& getOscillator2() { return osc2; }
    adsrData& getADSR() { return adsr; }
    
private:

    juce::AudioBuffer<float> synthBuffer;

    
    FilterData filter;
    adsrData filterADSR;
    OscData osc1;
    OscData osc2;
    adsrData adsr;
    bool isPrepared { false };
};

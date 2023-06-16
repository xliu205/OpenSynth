/*
  ==============================================================================

    SynthVoice.cpp
    Created: 28 Apr 2023 1:33:24pm
    Author:  Andy Truss

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) {
    // return true if sound is of type juce::SynthesiserSound
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) {
    osc1.setOscillatorFrequency(midiNoteNumber);
    osc2.setOscillatorFrequency(midiNoteNumber);
    adsr.noteOn();
    filterADSR.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff) {
    adsr.noteOff();
        filterADSR.noteOff();
        if (!allowTailOff || !adsr.isActive())
            clearCurrentNote();
        std::cout << "Note Off" << std::endl;
    
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue) {
    
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue) {
    
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels) {
    adsr.setSampleRate(sampleRate);
    
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
    
    osc1.prepareToPlay (spec);
    osc2.prepareToPlay (spec);
    filterADSR.setSampleRate(sampleRate);
      filter.prepareToPlay(sampleRate, samplesPerBlock, outputChannels);
      adsr.setSampleRate(sampleRate);

    
    isPrepared = true;
}



void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) {
    jassert(isPrepared);
    
    if(! isVoiceActive())
        return;
    
    
    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);

    synthBuffer.clear();
    
    //change so audioblock takes in synthBuffer instead of outputBuffer
    juce::dsp::AudioBlock<float> audioBlock { synthBuffer };
    // TODO: Create separate buffers for osc 1 and 2, then add them
    osc1.getNextAudioBlock(audioBlock);
    osc2.getNextAudioBlock(audioBlock);
    adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    filter.process(synthBuffer);
    filterADSR.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

    
    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
        outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);
        
        if(! adsr.isActive())
            clearCurrentNote();
        
    }
}

void SynthVoice::updateFilter(const int filterType, const float cutoff, const float resonance)
{
    auto modulator = filterADSR.getNextSample();
    filter.updateFilterParameters(filterType, cutoff, resonance, modulator);
}

/*
  ==============================================================================

    SynthSound.h
    Created: 28 Apr 2023 1:34:20pm
    Author:  Andy Truss

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound {
public:
    bool appliesToNote(int midiNoteNumber) override { return true; }
    bool appliesToChannel(int midiChannel) override { return true; }
};

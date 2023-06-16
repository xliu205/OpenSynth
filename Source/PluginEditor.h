/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
    The plugin editor is where all of the individual plugin components are
    initialized (oscillators, filter, and envelopes).

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/OscComponent.h"
#include "UI/adsrComponent.h"
#include "UI/FilterComponent.h"


//==============================================================================

class OpenSynthAudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    OpenSynthAudioProcessorEditor (OpenSynthAudioProcessor&);
    ~OpenSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    void sliderValueChanged(juce::Slider* slider) override;


    OpenSynthAudioProcessor& audioProcessor;
    
    OscComponent osc1;
    OscComponent osc2;
    
    FilterComponent filter1;
    
    //important to initialize adsrcomponent after the audioprocessor
    adsrComponent adsr1;
    adsrComponent adsr2;
    
    
    juce::Slider midiVolume; // [1]
    
    juce::TooltipWindow tip;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenSynthAudioProcessorEditor)
    
};

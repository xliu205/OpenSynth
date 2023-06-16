/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.
    The plugin editor is where all of the individual plugin components are
    initialized (oscillators, filter, and envelopes).

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
OpenSynthAudioProcessorEditor::OpenSynthAudioProcessorEditor (OpenSynthAudioProcessor& p)
: AudioProcessorEditor (&p)
, audioProcessor (p)
, osc1 (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1OCTAVE", "OSC1TUNE", "OSC1SHAPE", "OSC1VOLUME")
, osc2(audioProcessor.apvts, "OSC2WAVETYPE", "OSC2OCTAVE", "OSC2TUNE", "OSC2SHAPE", "OSC2VOLUME")
, filter1(audioProcessor.apvts, "FILTER1TYPE", "FILTER1CUTOFF", "FILTER1RESONANCE")
, adsr1 (audioProcessor.apvts, "ATTACK1", "DECAY1", "SUSTAIN1", "RELEASE1")
, adsr2 (audioProcessor.apvts, "ATTACK2", "DECAY2", "SUSTAIN2", "RELEASE2")
, tip (this, 200)

//above is the initializer list
{
    // setting size of plugin window
    setSize (850, 800);
    
    // make oscillator visible
    addAndMakeVisible(osc1);
    addAndMakeVisible(osc2);
   
    // make filter visible
    addAndMakeVisible(filter1);
    
    // make adsr visible
    addAndMakeVisible(adsr1);
    addAndMakeVisible(adsr2);
    
    // tooltip
    addAndMakeVisible(tip);
    

}

OpenSynthAudioProcessorEditor::~OpenSynthAudioProcessorEditor()
{
}

//==============================================================================
void OpenSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::cadetblue);
    g.setColour (juce::Colours::black);
    g.setFont (20.0f);
    g.drawFittedText ("Oscillator 1", 50, 0, 235, 30, juce::Justification::centred, 1);
    g.drawFittedText("Oscillator 2", 300, 0, 235, 30, juce::Justification::centred, 1);
    g.drawFittedText ("Filter", 50, 390, 235, 30, juce::Justification::centred, 1);
    g.drawFittedText ("Filter Envelope", 300, 390, 235, 30, juce::Justification::centred, 1);
    g.drawFittedText("Volume Envelope", 575, 155, 235, 30, juce::Justification::centred, 1);

    
}

/* This function sets up the orientation of each of the plugin's components within the editor.
 */
void OpenSynthAudioProcessorEditor::resized()
{
    
    osc1.setBounds (50, 40, 235, 300);
    osc2.setBounds (300, 40, 235, 300);
    filter1.setBounds (50, 430, 235, 300);
    adsr1.setBounds (575, 195, 235, 300);
    adsr2.setBounds (300, 430, 235, 300);
}


void OpenSynthAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    audioProcessor.noteonVel = midiVolume.getValue();
}

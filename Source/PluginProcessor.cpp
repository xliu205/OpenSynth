/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
OpenSynthAudioProcessor::OpenSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
    for (int i = 0; i < 5; ++i)
        synth.addVoice(new SynthVoice());

    synth.addSound(new SynthSound());

   
}

OpenSynthAudioProcessor::~OpenSynthAudioProcessor()
{
}

//==============================================================================
const juce::String OpenSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool OpenSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool OpenSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool OpenSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double OpenSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int OpenSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int OpenSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void OpenSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String OpenSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void OpenSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void OpenSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{

    //filter
    synth.setCurrentPlaybackSampleRate(sampleRate);
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumOutputChannels();

    
    for (int i=0; i<synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }
    

}


void OpenSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool OpenSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif


void OpenSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    for (int i=0; i<synth.getNumVoices(); ++i) {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) {
            // Osc controls
            // ADSR
            // LFO
            // Osc select
            auto& waveform1Choice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& waveform2Choice = *apvts.getRawParameterValue("OSC2WAVETYPE");
            
            // Pitch params
            auto& osc1Octave = *apvts.getRawParameterValue("OSC1OCTAVE");
            auto& osc1Tune = *apvts.getRawParameterValue("OSC1TUNE");
            auto& osc2Octave = *apvts.getRawParameterValue("OSC2OCTAVE");
            auto& osc2Tune = *apvts.getRawParameterValue("OSC2TUNE");
            
            // Volume params
            auto& osc1Volume = *apvts.getRawParameterValue("OSC1VOLUME");
            auto& osc2Volume = *apvts.getRawParameterValue("OSC2VOLUME");
            
            auto& attack = *apvts.getRawParameterValue ("ATTACK1");
            auto& decay = *apvts.getRawParameterValue("DECAY1");
            auto& sustain = *apvts.getRawParameterValue("SUSTAIN1");
            auto& release = *apvts.getRawParameterValue("RELEASE1");
            //load method notes that the values are atomic floats
            
            auto& filterType = *apvts.getRawParameterValue("FILTER1TYPE");
            auto& filterCutoff = *apvts.getRawParameterValue("FILTER1CUTOFF");
            auto& filterResonance = *apvts.getRawParameterValue("FILTER1RESONANCE");
            // Filter ADSR
            auto& filterAttack = *apvts.getRawParameterValue("ATTACK2");
            auto& filterDecay = *apvts.getRawParameterValue("DECAY2");
            auto& filterSustain = *apvts.getRawParameterValue("SUSTAIN2");
            auto& filterRelease = *apvts.getRawParameterValue("RELEASE2");
            
            
            voice->getOscillator1().setOscillatorWaveform(waveform1Choice);
            voice->getOscillator1().setPitchParameters(osc1Octave, osc1Tune);
            voice->getOscillator1().setVolume(osc1Volume);
            
            voice->getOscillator2().setOscillatorWaveform(waveform2Choice);
            voice->getOscillator2().setPitchParameters(osc2Octave, osc2Tune);
            voice->getOscillator2().setVolume(osc2Volume);
            //
            voice->getADSR().updateADSR(attack.load(), decay.load(), sustain.load(), release.load());
           voice->updateFilter(filterType, filterCutoff, filterResonance);
           voice->getFilterADSR().updateADSR(filterAttack.load(), filterDecay.load(), filterSustain.load(), filterRelease.load());
           
        }
    }

    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}


//==============================================================================
bool OpenSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* OpenSynthAudioProcessor::createEditor()
{
    return new OpenSynthAudioProcessorEditor (*this);
}

//==============================================================================
void OpenSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void OpenSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new OpenSynthAudioProcessor();
}

// Value Tree

juce::AudioProcessorValueTreeState::ParameterLayout OpenSynthAudioProcessor::createParams()
{


    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    //OSC selection

    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "Oscillator 1",
        juce::StringArray{ "Sine", "Saw", "Square", "White Noise"}, 0));
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2WAVETYPE", "Oscillator 2",
        juce::StringArray{ "Sine", "Saw", "Square", "White Noise"}, 0));
    
    // Octave and Tune
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1OCTAVE", "Osc 1 Octave",
        juce::NormalisableRange<float>{-2.0f, 2.0f, 1.0f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2OCTAVE", "Osc 2 Octave",
        juce::NormalisableRange<float>{-2.0f, 2.0f, 1.0f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1TUNE", "Osc 1 Tune",
        juce::NormalisableRange<float>{-12.0f, 12.0f, 0.1f }, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2TUNE", "Osc 2 Tune",
        juce::NormalisableRange<float>{-12.0f, 12.0f, 0.1f }, 0.0f));
    
    // Volume
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1VOLUME", "Osc 1 Volume",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 0.5f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC2VOLUME", "Osc 2 Volume",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 0.5f));

    // FM
    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQUENCY", "Osc 1 FM Frequency",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.6f}, 0.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "Osc 1 FM Depth",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.6f}, 0.0f));

    //ASDR
    params.push_back (std::make_unique<juce::AudioParameterFloat>("ATTACK1", "Attack", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("DECAY1", "Decay", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 0.1f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("SUSTAIN1", "Sustain", juce::NormalisableRange<float> { 0.1f, 1.0f, 0.1f }, 1.0f));
    params.push_back (std::make_unique<juce::AudioParameterFloat>("RELEASE1", "Release", juce::NormalisableRange<float> { 0.1f, 3.0f, 0.1f }, 0.4f));

    // Filter ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK2", "Filter Attack",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 0.06f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY2", "Filter Decay",
        juce::NormalisableRange<float>{0.01f, 1.0f, 0.01f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN2", "Filter Sustain",
        juce::NormalisableRange<float>{0.0f, 1.0f, 0.01f }, 1.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE2", "Filter Release",
        juce::NormalisableRange<float>{0.01f, 5.0f, 0.01f }, 0.25f));
    
    // Filter
    params.push_back(std::make_unique<juce::AudioParameterChoice>("FILTER1TYPE", "Filter Type",
        juce::StringArray{ "lowpass", "bandpass", "highpass" }, 0));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER1CUTOFF", "Filter Cutoff",
        juce::NormalisableRange<float>{20.0f, 20000.0f, 0.01f, 0.6f }, 20000.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FILTER1RESONANCE", "Filter Resonance",
        juce::NormalisableRange<float>{1.0f, 10.0f, 0.01f }, 1.0f));
    
    return { params.begin(), params.end() };
}


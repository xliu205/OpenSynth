/*
 ==============================================================================

   OscData.h
   Created: 5 May 2023 7:29:21pm
   Author:  Makayla McPherson

 ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


/*
 This class represents the data that each of our oscillators collects, which is based on
 the user's selection of wave as well as their interactions with the MIDI keyboard and
 sliders.
 */
class OscData : public juce::dsp::Oscillator<float>
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec& proc);
    void setOscillatorWaveform(const int waveformChoice);
    void setOscillatorFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setPitchParameters(const float octave, const float tune);
    void setVolume(const float volume);

private:
    juce::dsp::Oscillator<float> fmOscillator{ [](float x) { return std::sin(x); } };
    juce::dsp::Gain<float> gain;
    int lastMidiNotePressed { 0 };
    float pitchFactor { 1.0f };
    float fmDepth { 0.0f };
    float volume { 1.0 };
    };

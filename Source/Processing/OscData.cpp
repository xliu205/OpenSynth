/*
  ==============================================================================

    OscData.cpp
    Created: 5 May 2023 7:29:21pm
    Author:  Makayla McPherson

  ==============================================================================
*/

#include "OscData.h"
#include <cmath>



void OscData::prepareToPlay(juce::dsp::ProcessSpec& proc)
{
    prepare(proc);
    fmOscillator.prepare(proc);
    gain.prepare(proc);
}

void OscData::setOscillatorWaveform(const int waveformChoice)
{
    // Sin Wave: std::sin(x);
    // Saw wave: x / juce::MathConstants<float>::pi;
    // Square wave  x < 0.0f ? -1.0f : 1.0f;

    switch (waveformChoice)
    {
        case 0:
            // Sin wave
            initialise([](float x) { return std::sin(x); });
            break;

        case 1:
            // Saw wave
            initialise([](float x) { return x / juce::MathConstants<float>::pi; });
            break;

        case 2:
            // Square wave
            initialise([](float x) { return x < 0.0f ? -1.0f : 1.0f; });
            break;

        case 3:
            // White noise
            initialise([](float x) { return juce::Random::getSystemRandom().nextFloat() * x - x/2;});
            break;

        default:
            jassertfalse;
            break;
    }
}

void OscData::setOscillatorFrequency(const int midiNoteNumber)
{
    float midi = juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber);
    float freq = midi*pitchFactor;
    setFrequency(freq);
    
    lastMidiNotePressed = midiNoteNumber;
    std::cout << "Midi Freq: " << midi << std::endl;
    std::cout << "Pitch Factor: " << pitchFactor << std::endl;
    std::cout << "Osc1 Freq: " << freq << "\n";
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setVolume(const float volume) {
    gain.setGainLinear(volume);
}

void OscData::setPitchParameters(const float octave, const float tune) {
    // octave from -2 to +2
    float octaveFactor = pow(2, octave);
    
    // tune from -1 octave to +1 octave (measured in half-steps
    /* according to http://msp.ucsd.edu/techniques/v0.08/book-html/node8.html#:~:text=A%20half%20step%20comes%20to,pitch%20of%20a%20musical%20tone.
     f = 440 * 2^((m-69)/12)
     generalizing, f1 = f0 * 2^(m/12)
     */
    float tuneFactor = pow(2, tune/12);
    
    pitchFactor = octaveFactor * tuneFactor;

}

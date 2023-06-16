/*
  ==============================================================================

    FilterData.cpp
    Created: 11 May 2023 10:04:44pm
    Author:  lisa liu

  ==============================================================================
*/

#include "FilterData.h"


void FilterData::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;

    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputChannels;

    filter.prepare(spec);
    isPrepared = true;
}

void FilterData::process(juce::AudioBuffer<float>& buffer)
{
    jassert(isPrepared);
    juce::dsp::AudioBlock<float> block(buffer);
    filter.process(juce::dsp::ProcessContextReplacing<float>(block));
}

void FilterData::updateFilterParameters(const int filterType, const float frequency, const float resonance,
    const float modulator)
{
    switch (filterType)
    {
        case 0:
            filter.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;

        case 1:
            filter.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;

        case 2:
            filter.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;

        default:
            jassertfalse;
            break;
    }

    float modulatedFrequency = frequency * modulator;
    modulatedFrequency = std::fmax(std::fmin(modulatedFrequency, 20000.0f), 20.0f);

    filter.setCutoffFrequency(modulatedFrequency);
    filter.setResonance(resonance);
}

void FilterData::resetFilter()
{
    filter.reset();
}

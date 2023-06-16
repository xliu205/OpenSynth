//
//  LowpassHighpassFilter.hpp
//  OpenSynth
//
//  Created by lisa liu on 5/7/23.
//

#pragma once
#include <vector>
#include "JuceHeader.h"

class LowpassHighpassFilter {
public:
  // setters
  void setHighpass(bool highpass);
  void setCutoffFrequency(float cutoffFrequency);
  void setSamplingRate(float samplingRate);

  // Does not necessarily need to use JUCE's audio buffer
  void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&);

private:
  bool highpass;
  float cutoffFrequency;
  float samplingRate;

  // allpass filters' buffers: 1 sample per channel
  std::vector<float> dnBuffer;
};

class LowpassHighpassFilterAudioProcessor : public juce::AudioProcessor
{
//...
private:
    // our plugin's parameters
    juce::AudioProcessorValueTreeState parameters;
    std::atomic<float>* cutoffFrequencyParameter = nullptr;
    std::atomic<float>* highpassParameter = nullptr;
    
    // the filter implemented in listings 1-3
    LowpassHighpassFilter filter;
};


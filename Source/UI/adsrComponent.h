/*
  ==============================================================================

    adsrComponent.h
    Created: 5 May 2023 6:14:38pm
    Author:  Makayla McPherson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/*
 This class represents our ADSR/envelope component, which is where the user can adjust
 attack, decay, sustain, and release sliders.
*/
class adsrComponent  : public juce::Component
{
public:
    adsrComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackID,
        juce::String decayID, juce::String sustainID, juce::String releaseID);
    ~adsrComponent() override;
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    juce::String componentName = "";

    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;

    // when exiting UI, unique_ptr marks memory as free to use
    std::unique_ptr<Attachment> attackAttachment;
    std::unique_ptr<Attachment> decayAttachment;
    std::unique_ptr<Attachment> sustainAttachment;
    std::unique_ptr<Attachment> releaseAttachment;
    
    juce::Label attackLabel { "Attack", "Attack" };
    juce::Label decayLabel { "Decay", "Decay" };
    juce::Label sustainLabel {"Sustain", "Sustain"};
    juce::Label releaseLabel {"Release", "Release"};
    
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (adsrComponent)
};

/*
  ==============================================================================

    FilterComponent.h
    Created: 7 May 2023 5:07:14pm
    Author:  Karma Selsey

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 This class represents our filter component, which is where the user can select a
 filter type and adjust cutoff and resonance.
*/

class FilterComponent  : public juce::Component
{
public:
    FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeID,
            juce::String filterCutoffID, juce::String filterResonanceID);
    ~FilterComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::ComboBox filterTypes;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> filterTypeAttachment;
    juce::Label filterTypeLabel { "Filter Type", "Filter Type" };
    juce::Slider filterCutoffSlider;
    juce::Slider filterResonanceSlider;
    juce::Label filterCutoffLabel{ "Cutoff", "Cutoff" };
    juce::Label filterResonanceLabel{ "Resonance", "Resonance" };
    juce::ToggleButton bypass;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterCutoffAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> filterResonanceAttachment;

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment);


        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FilterComponent)
};

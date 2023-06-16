/*
  ==============================================================================

    OscComponent.h
    Created: 5 May 2023 8:07:38pm
    Author:  Makayla McPherson

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

/*
 This class represents our oscillator componenst, which is where the user can adjust tune,
 octave, and volume.
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String octaveID, juce::String tuneID, juce::String shapeID, juce::String volumeID);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    juce::ComboBox oscWaveSelect;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectAttachment;
    
    juce::Slider octaveSlider;
    juce::Slider tuneSlider;
    juce::Slider shapeSlider;
    juce::Slider volumeSlider;
    
    std::unique_ptr<Attachment> octaveAttachment;
    std::unique_ptr<Attachment> tuneAttachment;
    std::unique_ptr<Attachment> shapeAttachment;
    std::unique_ptr<Attachment> volumeAttachment;
    
    juce::Label waveSelectLabel { "Wave Type", "Wave Type" };
    juce::Label octaveLabel { "Octave", "Octave" };
    juce::Label tuneLabel { "Tune", "Tune" };
    juce::Label shapeLabel { "Shape", "Shape" };
    juce::Label volumeLabel { "Volume", "Volume" };
    
    void setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};

/*
  ==============================================================================

    adsrComponent.cpp
    Created: 5 May 2023 6:14:38pm
    Author:  Makayla McPherson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "adsrComponent.h"
//important principal: encapsulation --> dont give your class more access than it needs

//==============================================================================
adsrComponent::adsrComponent(juce::AudioProcessorValueTreeState& apvts, juce::String attackID,
    juce::String decayID, juce::String sustainID, juce::String releaseID)
{

    setSliderWithLabel(attackSlider, attackLabel, apvts, attackID, attackAttachment);
    attackLabel.setTooltip("Set the time for the envelope to reach its peak value");
    setSliderWithLabel(decaySlider, decayLabel, apvts, decayID, decayAttachment);
    decayLabel.setTooltip("Set the time for the envelope to drop from peak to sustain value");
    setSliderWithLabel(sustainSlider, sustainLabel, apvts, sustainID, sustainAttachment);
    sustainLabel.setTooltip("Set the amplitude of the value on a held note");
    setSliderWithLabel(releaseSlider, releaseLabel, apvts, releaseID, releaseAttachment);
    releaseLabel.setTooltip("Set the time to drop to zero when a note is released");
}

adsrComponent::~adsrComponent()
{
}

void adsrComponent::paint (juce::Graphics& g)
{
 

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
}

void adsrComponent::resized()
{
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
 
    attackSlider.setBounds (20, 60, 50, 200);
    attackLabel.setBounds (attackSlider.getX(), attackSlider.getY() - labelYOffset, attackSlider.getWidth(), labelHeight);
    decaySlider.setBounds (70, 60, 50, 200);
    decayLabel.setBounds (decaySlider.getX(), decaySlider.getY() - labelYOffset, decaySlider.getWidth(), labelHeight);
    sustainSlider.setBounds(120, 60, 50, 200);
    sustainLabel.setBounds (sustainSlider.getX(), sustainSlider.getY() - labelYOffset, sustainSlider.getWidth(), labelHeight);
    releaseSlider.setBounds(170, 60, 50, 200);
    releaseLabel.setBounds (releaseSlider.getX(), releaseSlider.getY() - labelYOffset, releaseSlider.getWidth(), labelHeight);

}

//following "dry" conventions of ton repeating yourself in code too much
void adsrComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible (slider);
    
    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);
    
    label.setColour (juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont (14.0f);
    label.setJustificationType (juce::Justification::centred);
    addAndMakeVisible (label);
}

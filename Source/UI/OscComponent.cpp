/*
  ==============================================================================

    OscComponent.cpp
    Created: 5 May 2023 8:07:38pm
    Author:  Makayla McPherson

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String octaveID, juce::String tuneID, juce::String shapeID, juce::String volumeID)
{
    juce::StringArray choices { "Sin", "Saw", "Square", "Noise" };
    oscWaveSelect.addItemList (choices, 1);
    oscWaveSelect.setTooltip("Select the type of wave to be produced");
    addAndMakeVisible(oscWaveSelect);
    //connecting the users choice with the visualization they see
    oscWaveSelectAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,waveSelectorId, oscWaveSelect );
    
    setSliderWithLabel (octaveSlider, octaveLabel, apvts, octaveID, octaveAttachment);
    octaveLabel.setTooltip("Pitch the oscilator up or down in octaves");
    setSliderWithLabel (tuneSlider, tuneLabel, apvts, tuneID, tuneAttachment);
    tuneLabel.setTooltip("Pitch the oscilator up or down by semitones");
    setSliderWithLabel(volumeSlider, volumeLabel, apvts, volumeID, volumeAttachment);
    volumeLabel.setTooltip("Controls the level of the oscillator");
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    g.drawFittedText("Wave Type", 10, 0, 55, 40, juce::Justification::centred, 1);
}

/*
 This function sets the bounds for each slider and its associated labels.
 */
void OscComponent::resized()
{
    const auto labelYOffset = 20;
    const auto labelHeight = 20;
    
    oscWaveSelect.setBounds (10, 30, 60, 30);
    
    tuneSlider.setBounds (40, 90, 50, 200);
    tuneLabel.setBounds (tuneSlider.getX(), tuneSlider.getY() - labelYOffset, tuneSlider.getWidth(), labelHeight);
    
    octaveSlider.setBounds (90, 90, 50, 200);
    octaveLabel.setBounds (octaveSlider.getX(), octaveSlider.getY() - labelYOffset, octaveSlider.getWidth(), labelHeight);

    volumeSlider.setBounds (140, 90, 50, 200);
    volumeLabel.setBounds (volumeSlider.getX(), volumeSlider.getY() - labelYOffset, volumeSlider.getWidth(), labelHeight);
}

/*
 This function sets up the types and orientations of the sliders given a slider, label,
 audio processor tree, parameter ID, and slider attachment.
 */
void OscComponent::setSliderWithLabel (juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
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

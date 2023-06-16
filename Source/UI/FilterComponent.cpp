/*
  ==============================================================================

    FilterComponent.cpp
    Created: 7 May 2023 5:07:14pm
    Author:  Karma Selsey

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filterTypeID,
                                 juce::String filterCutoffID, juce::String filterResonanceID)
{
    juce::StringArray filterChoices = { "Lowpass", "Bandpass", "Highpass" };
    filterTypes.addItemList(filterChoices, 1);
    addAndMakeVisible(filterTypes);
    filterTypes.setTooltip("Select the type of filter to be applied");

    filterTypeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filterTypeID, filterTypes);

    filterTypeLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterTypeLabel.setFont(14.0f);
    filterTypeLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(filterTypeLabel);

    setSliderWithLabel(filterCutoffSlider, filterCutoffLabel, apvts, filterCutoffID, filterCutoffAttachment);
    filterCutoffLabel.setTooltip("Set the frequency at which the filter begins to cut down the signal");
    setSliderWithLabel(filterResonanceSlider, filterResonanceLabel, apvts, filterResonanceID, filterResonanceAttachment);
    filterResonanceLabel.setTooltip("Set how much the signal is boosted near the cutoff frequency");


}

FilterComponent::~FilterComponent()
{
}

// colors and font for component
void FilterComponent::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
}

/*
 This function sets up the bounds and sizes of the different sliders, a dropdown list, and
 their associated labels.
 */
void FilterComponent::resized()
{
    const auto startYPos = 30;
        const auto sliderWidth = 50;
        const auto sliderHeight = 200;
        const auto labelYOffset = 20;
        const auto labelHeight = 20;

        filterTypes.setBounds(75, startYPos, 90, 30);
        filterTypeLabel.setBounds(78, startYPos - labelYOffset, 78, labelHeight);

        filterCutoffSlider.setBounds(55, 90, sliderWidth, sliderHeight);
        filterCutoffLabel.setBounds(filterCutoffSlider.getX(), filterCutoffSlider.getY() - labelYOffset,
            filterCutoffSlider.getWidth(), labelHeight);
        filterResonanceSlider.setBounds(135, 90, sliderWidth, sliderHeight);
        filterResonanceLabel.setBounds(filterResonanceSlider.getX(), filterResonanceSlider.getY() - labelYOffset,
            filterResonanceSlider.getWidth()+10, labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

/*
 This function sets up the types and orientations of the sliders given a slider, label,
 audio processor tree, parameter ID, and slider attachment.
 */
void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
    juce::String parameterID, std::unique_ptr<Attachment>& sliderAttachment)
{
    slider.setSliderStyle(juce::Slider::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    slider.setColour(juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::white);
    addAndMakeVisible(slider);

    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, parameterID, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(14.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}

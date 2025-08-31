/*
  ==============================================================================

    OscComponent.cpp
    Created: 13 Jul 2025 12:20:04am
    Author:  dvles

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId)
{
	juce::StringArray choices{
		"Sine",
		"Saw",
		"Square"
	};

	oscWaveSelector.addItemList(choices, 1); // Add items to the ComboBox
	addAndMakeVisible(oscWaveSelector); // Make the ComboBox visible

	oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts,
        waveSelectorId, oscWaveSelector);

	

	setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqAttachment);

	setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttachment); //watch out

}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{


}

void OscComponent::resized()
{
	const auto sliderPosY = 80; // Y position for the sliders
	const auto sliderWidth = 100; // Width of the sliders
	const auto sliderHeight = 90; // Height of the sliders
	const auto labelYOffset = 20; // Offset for the label above the slider
	const auto labelHeight = 20; // Height of the label


	oscWaveSelector.setBounds(0, 0,90, 20); // Set the bounds of the ComboBox
	fmFreqSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight); // Set the bounds of the FM frequency slider
	fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);  // Set the bounds of the FM frequency label

	fmDepthSlider.setBounds(fmFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight); // Set the bounds of the FM depth slider

	fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight); // Set the bounds of the FM depth label
}
using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, 
	juce::String paramId, std::unique_ptr<Attachment>& attachment) {

	slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);


	slider.setColour(juce::Slider::thumbColourId, juce::Colours::orange); // Change to your desired color
	slider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);

	addAndMakeVisible(slider);

	attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

	label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white); // Set the text color of the label
	label.setFont(15.0f); // Set the font size of the label
	label.setJustificationType(juce::Justification::centred); // Center the text in the label
	addAndMakeVisible(label); // Make the FM frequency slider visible

}
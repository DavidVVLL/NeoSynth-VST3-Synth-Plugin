/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 10 Jul 2025 6:50:40pm
    Author:  dvles

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    attackAttachment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.



    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);



    attackLabel.setText("A", juce::dontSendNotification);
    decayLabel.setText("D", juce::dontSendNotification);
    sustainLabel.setText("S", juce::dontSendNotification);
    releaseLabel.setText("R", juce::dontSendNotification);

    addAndMakeVisible(attackLabel);
    addAndMakeVisible(decayLabel);
    addAndMakeVisible(sustainLabel);
    addAndMakeVisible(releaseLabel);



}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint(juce::Graphics& g)
{
}

void AdsrComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..


    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;

    const auto sliderWidth = 30; 





    // Calculate the total width needed and center the sliders horizontally
    const auto sliderstartX = bounds.getWidth() / 8;
    const auto sliderstartY = 20;
    const int labelHeight = 20;


    const auto sliderHeight = 150;



    attackSlider.setBounds(sliderstartX, sliderstartY, sliderWidth, sliderHeight);

    decaySlider.setBounds(attackSlider.getRight() + padding, sliderstartY, sliderWidth, sliderHeight);

    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderstartY, sliderWidth, sliderHeight);

    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderstartY, sliderWidth, sliderHeight);


    attackLabel.setBounds(attackSlider.getX(), attackSlider.getBottom(), sliderWidth, labelHeight);
    decayLabel.setBounds(decaySlider.getX(), decaySlider.getBottom(), sliderWidth, labelHeight);
    sustainLabel.setBounds(sustainSlider.getX(), sustainSlider.getBottom(), sliderWidth, labelHeight);
    releaseLabel.setBounds(releaseSlider.getX(), releaseSlider.getBottom(), sliderWidth, labelHeight);



}

void AdsrComponent::setSliderParams(juce::Slider& slider) {

    slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
    addAndMakeVisible(slider);
}
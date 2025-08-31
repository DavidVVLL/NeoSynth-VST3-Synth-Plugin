/*
  ==============================================================================

    OscComponent.h
    Created: 13 Jul 2025 12:20:04am
    Author:  dvles

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:




	juce::ComboBox oscWaveSelector; // ComboBox for selecting wave type
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;
	
    juce::Slider fmFreqSlider; // Slider for FM frequency

    juce::Slider fmDepthSlider; // Slider for FM depth

    using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;


	std::unique_ptr<Attachment> fmFreqAttachment;
	std::unique_ptr<Attachment> fmDepthAttachment;




	juce::Label fmFreqLabel { "FM Frequency", "FM Frequency" }; // Label for FM frequency slider
	juce::Label fmDepthLabel{ "FM Depth", "FM Depth" }; // Label for FM depth slider



    void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts,
        juce::String paramId, std::unique_ptr<Attachment>& attachment);
	

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)


};

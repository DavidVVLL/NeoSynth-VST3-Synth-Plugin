/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NeoSynthAudioProcessorEditor::NeoSynthAudioProcessorEditor (NeoSynthAudioProcessor& p)
	: AudioProcessorEditor(&p), audioProcessor(p),osc (audioProcessor.apvts, "OSC1WAVETYPE",
		"OSC1FMREQ", "OSC1FMDEPTH"), adsr(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 400);
	addAndMakeVisible(osc); // Add the OscComponent to the editor
	

  
    //make adsr visible
	addAndMakeVisible(adsr);


    


}

NeoSynthAudioProcessorEditor::~NeoSynthAudioProcessorEditor()
{
}

//==============================================================================
void NeoSynthAudioProcessorEditor::paint (juce::Graphics& g)
{

	background = juce::ImageCache::getFromMemory(BinaryData::Neon_Lines_on_Vintage_Synthesizer_png, BinaryData::Neon_Lines_on_Vintage_Synthesizer_pngSize);
	g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
	
}

void NeoSynthAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	adsr.setBounds(getWidth() / 2, 40, getWidth() / 2, getHeight());

	osc.setBounds(40, 40, 180, 200); // Set the bounds of the OscComponent to the left half of the editor

    

}




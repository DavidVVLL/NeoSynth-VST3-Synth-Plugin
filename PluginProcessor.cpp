/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NeoSynthAudioProcessor::NeoSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
	apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
	synth.addSound(new SynthSound());
	synth.addVoice(new SynthVoice());
	
}

NeoSynthAudioProcessor::~NeoSynthAudioProcessor()
{
}

//==============================================================================
const juce::String NeoSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NeoSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NeoSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif

}

bool NeoSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NeoSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NeoSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NeoSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NeoSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NeoSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void NeoSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NeoSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    synth.setCurrentPlaybackSampleRate(sampleRate);

	for (int i = 0; i < synth.getNumVoices(); ++i)
	{
		if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
		{
			voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
		}
	}
}

void NeoSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NeoSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void NeoSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    


	for (int i = 0; i < synth.getNumVoices(); ++i)
	{
		if (auto* voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
		{
			// Here you can access each voice and do something with it if needed
			// For example, you could adjust parameters or check the state of the voice

            auto& attack = *apvts.getRawParameterValue("ATTACK");
			auto& decay = *apvts.getRawParameterValue("DECAY");
			auto& sustain = *apvts.getRawParameterValue("SUSTAIN");
			auto& release = *apvts.getRawParameterValue("RELEASE");
            auto& oscWaveChoice = *apvts.getRawParameterValue("OSC1WAVETYPE");
            auto& fmDepth = *apvts.getRawParameterValue("OSC1FMDEPTH");

            auto& fmFreq = *apvts.getRawParameterValue("OSC1FMFREQ");

\
            voice->getOscillator().setWaveType(oscWaveChoice); // Set the oscillator wave type based on the parameter value
            voice->getOscillator().setFmParams(fmDepth, fmFreq);
			voice->update(
				attack.load(),
				decay.load(),
				sustain.load(),
				release.load()
			);

		}
	}


    
        
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	

}

//==============================================================================
bool NeoSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NeoSynthAudioProcessor::createEditor()
{
    return new NeoSynthAudioProcessorEditor (*this);
}

//==============================================================================
void NeoSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NeoSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NeoSynthAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout NeoSynthAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    //OSC SELECT
    params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1WAVETYPE", "OSC 1 Wave Type",
        juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    //FM

    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMFREQ", "Osc 1 FM Frequency", 
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.03f }, 5.0f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("OSC1FMDEPTH", "Osc 1 FM Depth",
        juce::NormalisableRange<float>{0.0f, 1000.0f, 0.01f, 0.03f }, 200.0f));
    
    //ADSR
    //params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "oscillator", juce::StringArray{ "Sine", "Saw", "Square" }, 0));
    //maybe not needed

    params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{0.1f,
        1.0f }, 0.1f ));

	params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{0.1f,
        1.0f }, 0.1f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{0.1f,
        1.0f }, 1.0f));

	params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{0.1f,
        3.0f }, 0.4f));
	

    


    return { params.begin(), params.end() };


}
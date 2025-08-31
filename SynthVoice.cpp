/*
  ==============================================================================

    SynthVoice.cpp
    Created: 6 Jul 2025 1:25:20am
    Author:  dvles

  ==============================================================================
*/
#pragma once
#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
	// Check if the sound is of type SynthSound
	return dynamic_cast<SynthSound*>(sound) != nullptr;
};

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) 
{
	osc.setWaveFrequency(midiNoteNumber);
	adsr.noteOn();
};

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{

	adsr.noteOff();


	if (!allowTailOff || !adsr.isActive())
	{
		clearCurrentNote();
	}
	
};
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
};

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
};

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{

	adsr.setSampleRate(sampleRate);
    juce::dsp::ProcessSpec spec; 
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;
	osc.prepareToPlay(spec);
    gain.prepare(spec);

    gain.setGainLinear(1.0f);


	isprepared = true; // Set the flag to true after preparation
};

void SynthVoice::update (const float attack, const float decay, const float sustain, const float release)
{
	adsr.update(attack, decay, sustain, release);
};

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{

	jassert(isprepared); // Ensure the voice is prepared before rendering
	 
	if (!isVoiceActive())
	{
		return;
	}



	synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
	synthBuffer.clear();

    juce::dsp::AudioBlock<float> audioBlock{ outputBuffer };

	osc.getNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());


	


    for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
    {
		outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

		if (!adsr.isActive()) {
			clearCurrentNote();
		}
    }
};


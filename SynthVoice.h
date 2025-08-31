/*
  ==============================================================================

    SynthVoice.h
    Created: 6 Jul 2025 1:25:20am
    Author:  dvles

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
	bool canPlaySound(juce::SynthesiserSound* sound) override;
	
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;


		void stopNote(float velocity, bool allowTailOff) override;

		void controllerMoved(int controllerNumber, int newControllerValue) override;

		void pitchWheelMoved(int newPitchWheelValue) override;

		void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
		
		void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;

		void update(const float attack, const float decay, const float sustain, const float release);

		OscData& getOscillator() { return osc; } // Getter for the oscillator data

private:
	AdsrData adsr; // ADSR envelope data
	juce::AudioBuffer<float> synthBuffer; // Buffer for storing the synthesized audio samples

	OscData osc; 


	//juce::dsp::Oscillator<float> osc{ [](float x) { return x / juce::MathConstants<float>::pi; }}; // Oscillator for generating audio sin wave
	//juce::dsp::Oscillator<float> osc{ [](float x) { return std::sin(x); },  }; // Oscillator for generating audio sin wave
	// return x / juce::MathConstants<float>::pi; // saw wave
	// return x < 0.0f  -1.0f : 1.0f; // sqaure wave

	juce::dsp::Gain<float> gain;
	bool isprepared{ false }; // Flag to check if the voice is prepared

};
/*
  ==============================================================================

    SynthSound.h
    Created: 6 Jul 2025 1:25:46am
    Author:  dvles

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
	bool appliesToNote(int midiNoteNumber) override
	{
		// This sound applies to all MIDI notes
		return true;
	};
	bool appliesToChannel(int midiChannel) override
	{
		// This sound applies to all MIDI channels
		return true;
	};
};
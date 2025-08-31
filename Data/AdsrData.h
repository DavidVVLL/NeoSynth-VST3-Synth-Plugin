/*
  ==============================================================================

    AdsrData.h
    Created: 10 Jul 2025 6:52:15pm
    Author:  dvles

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class AdsrData : public juce::ADSR
{
public:
    void update(const float attack, const float decay, const float sustain, const float release);


private:
    juce::ADSR::Parameters adsrParams; // Parameters for the ADSR envelope

};
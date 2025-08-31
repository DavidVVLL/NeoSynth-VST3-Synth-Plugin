/*
  ==============================================================================

    AdsrData.cpp
    Created: 10 Jul 2025 6:52:15pm
    Author:  dvles

  ==============================================================================
*/
#include "AdsrData.h"
#include "../SynthVoice.h"


void AdsrData::update(const float attack, const float decay, const float sustain, const float release)
{

	adsrParams.attack = attack;
	adsrParams.decay = decay;
	adsrParams.sustain = sustain;
	adsrParams.release = release;

	setParameters(adsrParams);
}

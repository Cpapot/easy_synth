/*
  ==============================================================================

    SynthSound.h
    Created: 3 Jun 2024 1:50:46pm
    Author:  coren

  ==============================================================================
*/

#pragma once

# include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
public:
    bool 	appliesToNote(int midiNoteNumber) override { return true; };
    bool 	appliesToChannel(int midiChannel) override { return true; };
};
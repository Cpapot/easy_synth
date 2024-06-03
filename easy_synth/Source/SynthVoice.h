/*
  ==============================================================================

    SynthVoice.h
    Created: 3 Jun 2024 1:50:18pm
    Author:  coren

  ==============================================================================
*/

#pragma once

# include "SynthSound.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:
    bool 	canPlaySound(juce::SynthesiserSound* sound) override;
    void 	startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void 	stopNote(float velocity, bool allowTailOff) override;
    void 	controllerMoved(int controllerNumber, int newControllerValue) override;
    void 	pitchWheelMoved(int newPitchWheelValue) override;
    void    prepareToPlay(double sampleRate, int samplesPerBlock, int outputsChannelsCount);
    void 	renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples) override;

private:
    juce::ADSR adsr;
    juce::ADSR::Parameters adsrParams;

    //juce::dsp::Oscillator<float> osc{ [](float x) {return std::sin(x);  } };                      //sin Wave
    juce::dsp::Oscillator<float> osc{ [](float x) {return x / juce::MathConstants<float>::pi;  } }; //Saw Wave
    //juce::dsp::Oscillator<float> osc{ [](float x) {return x < 0.0f ? -1.0f : 1.0f;  } };          //sqare wave
    juce::dsp::Gain<float> gain;


    bool    isPreparedtoPlay{ false };
};
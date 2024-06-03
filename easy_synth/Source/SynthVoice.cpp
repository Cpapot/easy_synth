/*
  ==============================================================================

    SynthVoice.cpp
    Created: 3 Jun 2024 1:50:18pm
    Author:  coren

  ==============================================================================
*/

#include "SynthVoice.h"

bool 	SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    if (dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr)
        return true;
    else
        return false;
}

void 	SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    adsr.noteOn();
}

void 	SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr.noteOff();

    if (allowTailOff == false || adsr.isActive() == false)
        clearCurrentNote();
}

void 	SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}

void 	SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}

void    SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputsChannelsCount)
{
    adsr.setSampleRate(sampleRate);

    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = outputsChannelsCount;
    spec.sampleRate = sampleRate;

    osc.prepare(spec);

    gain.prepare(spec);

    osc.setFrequency(220.0f);

    gain.setGainLinear(0.1f);

    isPreparedtoPlay = true;
}

void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
    adsrParams.attack = attack;
    adsrParams.decay = decay;
    adsrParams.sustain = sustain;
    adsrParams.release = release;

    adsr.setParameters(adsrParams);
}

void 	SynthVoice::renderNextBlock(juce::AudioBuffer< float >& outputBuffer, int startSample, int numSamples)
{
    //exit le prog si false
    jassert(isPreparedtoPlay);

    if (isVoiceActive() == false)
        return;

    synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, true);
    synthBuffer.clear();

    juce::dsp::AudioBlock<float> block{ synthBuffer };
    osc.process(juce::dsp::ProcessContextReplacing<float>(block));
    gain.process(juce::dsp::ProcessContextReplacing<float>(block));

    adsr.applyEnvelopeToBuffer(synthBuffer, 0, numSamples);

    if (startSample)
        jassertfalse;

    for (int i = 0; i != outputBuffer.getNumChannels(); i++)
    {
        outputBuffer.addFrom(i, startSample, synthBuffer, i, 0, numSamples);
        if (adsr.isActive() == false)
            clearCurrentNote();
    }
}
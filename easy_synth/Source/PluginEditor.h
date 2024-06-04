/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Easy_synthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Easy_synthAudioProcessorEditor (Easy_synthAudioProcessor&);
    ~Easy_synthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Easy_synthAudioProcessor& audioProcessor;

    juce::Slider    attackSlider;
    juce::Slider    decaySlider;
    juce::Slider    sustainSlider;
    juce::Slider    releaseSlider;
    juce::ComboBox  oscComboBox;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

    std::unique_ptr <SliderAttachment> attackAttachment;
    std::unique_ptr <SliderAttachment> decayAttachment;
    std::unique_ptr <SliderAttachment> sustainAttachment;
    std::unique_ptr <SliderAttachment> releaseAttachment;

    std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscAttachement;
    void setSliderParam(juce::Slider& slider);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Easy_synthAudioProcessorEditor)
};

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "ImageKnob.h"

//==============================================================================
/**
*/
class BreakdownerAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    BreakdownerAudioProcessorEditor (BreakdownerAudioProcessor&);
    ~BreakdownerAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

    juce::Image fondo;
    juce::Image knobImagen;
    juce::Image LED;

    std::unique_ptr<ImageKnob> knob1;
    juce::Label GainLabel;

    std::unique_ptr<ImageKnob> knob2;
    juce::Label DistLabel;
    
    std::unique_ptr<ImageKnob> knob3;
    juce::Label ToneLabel;
    
    std::unique_ptr<ImageKnob> knob4;
    juce::Label BlendLabel;

    /*juce::Slider sliderGain;
    juce::Slider sliderDist;
    juce::Slider sliderTone;
    juce::Slider sliderBlend;*/

    juce::ToggleButton ButtonBypass;

    std::unique_ptr<ImageKnob> LED1;

    juce::Typeface::Ptr SpecialElite;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BreakdownerAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BreakdownerAudioProcessorEditor)
};

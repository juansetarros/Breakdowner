/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BreakdownerAudioProcessorEditor::BreakdownerAudioProcessorEditor(BreakdownerAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{

    fondo = juce::ImageFileFormat::loadFrom(BinaryData::BreakDowner_png, BinaryData::BreakDowner_pngSize);
    knobImagen = juce::ImageFileFormat::loadFrom(BinaryData::BreakDownerKnob_png, BinaryData::BreakDownerKnob_pngSize);
    LED = juce::ImageFileFormat::loadFrom(BinaryData::BreakDownerLED_png, BinaryData::BreakDowner_pngSize);
    SpecialElite = juce::Typeface::createSystemTypefaceFor(BinaryData::SpecialElite_ttf,
        BinaryData::SpecialElite_ttfSize);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.

    // Gain Knob
    knob1.reset(new ImageKnob(knobImagen, 89, false));
    addAndMakeVisible(knob1.get());
    knob1->setRange(-96, 3);
    knob1->setValue(0);
    //knob1->setSkewFactorFromMidPoint(0);
    knob1->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    knob1->onValueChange = [this]
    {
        float lin = juce::Decibels::decibelsToGain(knob1->getValue());
        audioProcessor.gain = lin;
    };
    addAndMakeVisible(GainLabel);
    GainLabel.setText("GAIN", juce::dontSendNotification);
    GainLabel.setFont(juce::Font(SpecialElite).withHeight(13.0f));
    GainLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    GainLabel.setInterceptsMouseClicks(false, false);

    /*addAndMakeVisible(sliderGain);
    sliderGain.setSliderStyle(juce::Slider::Rotary);
    sliderGain.setRange(-96, 10);
    sliderGain.setValue(0);
    sliderGain.setSkewFactorFromMidPoint(0);
    sliderGain.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sliderGain.onValueChange = [this]
    {
        float lin = juce::Decibels::decibelsToGain(sliderGain.getValue());
        audioProcessor.gain = lin;
    };*/

    // Dist Knob
    knob2.reset(new ImageKnob(knobImagen, 89, false));
    addAndMakeVisible(knob2.get());
    knob2->setRange(0.3, 0.9);
    knob2->setValue(0.5);
    //knob2->setSkewFactorFromMidPoint(0.3);
    knob2->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    knob2->onValueChange = [this]
    {
        float inverted = 1.0f - knob2->getValue();
        audioProcessor.Clipper.setThreshold(inverted);
    };
    addAndMakeVisible(DistLabel);
    DistLabel.setText("DISTORTION", juce::dontSendNotification);
    DistLabel.setFont(juce::Font(SpecialElite).withHeight(15.0f));
    DistLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    DistLabel.setInterceptsMouseClicks(false, false);

    /*addAndMakeVisible(sliderDist);
    sliderDist.setSliderStyle(juce::Slider::Rotary);
    sliderDist.setRange(0.1, 0.9);
    sliderDist.setValue(0.7);
    sliderDist.setSkewFactorFromMidPoint(0.3);
    sliderDist.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sliderDist.onValueChange = [this]
    {
            audioProcessor.Clipper.setThreshold(sliderDist.getValue());
    };*/

    // Blend Knob
    knob3.reset(new ImageKnob(knobImagen, 89, false));
    addAndMakeVisible(knob3.get());
    knob3->setRange(0, 1);
    knob3->setValue(1);
    knob3->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    knob3->onValueChange = [this]
        {
            audioProcessor.Clipper.setBlend(knob3->getValue());
        };
    addAndMakeVisible(BlendLabel);
    BlendLabel.setText("BLEND", juce::dontSendNotification);
    BlendLabel.setFont(juce::Font(SpecialElite).withHeight(13.0f));
    BlendLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    BlendLabel.setInterceptsMouseClicks(false, false);

    /*addAndMakeVisible(sliderBlend);
    sliderBlend.setSliderStyle(juce::Slider::Rotary);
    sliderBlend.setRange(0.5, 1);
    sliderBlend.setValue(1);
    sliderBlend.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sliderBlend.onValueChange = [this]
    {
            audioProcessor.Clipper.setBlend(sliderBlend.getValue());
    };*/

    // Tone Knob (Lowpass Filter)
    knob4.reset(new ImageKnob(knobImagen, 89, false));
    addAndMakeVisible(knob4.get());
    knob4->setRange(1000, 16000);
    knob4->setValue(16000);
    knob4->setSkewFactorFromMidPoint(4000);
    knob4->setSliderStyle(juce::Slider::RotaryVerticalDrag);
    knob4->onValueChange = [this]
        {
            audioProcessor.LPF.changeFc(knob4->getValue());
        };
    addAndMakeVisible(ToneLabel);
    ToneLabel.setText("TONE", juce::dontSendNotification);
    ToneLabel.setFont(juce::Font(SpecialElite).withHeight(15.0f));
    ToneLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::antiquewhite);
    ToneLabel.setInterceptsMouseClicks(false, false);
    
    /*addAndMakeVisible(sliderTone);
    sliderTone.setSliderStyle(juce::Slider::Rotary);
    sliderTone.setRange(1000, 16000);
    sliderTone.setValue(16000);
    sliderTone.setSkewFactorFromMidPoint(4000);
    sliderTone.setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
    sliderTone.onValueChange = [this]
    {
            audioProcessor.LPF.changeFc(sliderTone.getValue());
    };*/

    LED1.reset(new ImageKnob(LED, 2, false));
    addAndMakeVisible(LED1.get());
    LED1->setRange(0, 1);
    LED1->setValue(0);
    LED1->setInterceptsMouseClicks(false, false);
    addAndMakeVisible(ButtonBypass);
    ButtonBypass.setButtonText("");
    ButtonBypass.setColour(juce::ToggleButton::tickColourId, juce::Colours::transparentBlack);
    ButtonBypass.setColour(juce::ToggleButton::tickDisabledColourId, juce::Colours::transparentBlack);
    ButtonBypass.onStateChange = [this]
    {
            audioProcessor.bypass = ButtonBypass.getToggleState();
            int LEDValue = ButtonBypass.getToggleState();
            LED1->setValue(LEDValue);
    };

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 450); 
}

BreakdownerAudioProcessorEditor::~BreakdownerAudioProcessorEditor()
{
}

//==============================================================================
void BreakdownerAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Rectangle<float> dimensiones = getBounds().toFloat();
    g.drawImage(fondo, dimensiones);

    g.setColour (juce::Colours::black);
    
}

void BreakdownerAudioProcessorEditor::resized()
{
    //Gain 
    knob1->setBounds(105, 130, 100, 100); 
    GainLabel.setBounds(85, 130, 100, 100);
    //Dist 
    knob2->setBounds(195, 20, 140, 140); 
    DistLabel.setBounds(220, -30, 140, 140);
    //Blend
    knob3->setBounds(200, 130, 100, 100);
    BlendLabel.setBounds(277, 130, 100, 100);
    //Tone
    knob4->setBounds(70, 20, 140, 140); 
    ToneLabel.setBounds(115, -30, 140, 140);
    
    //Toggle
    ButtonBypass.setBounds(185, 305, 50, 50);
    LED1->setBounds(162, 8, 75, 75);


    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

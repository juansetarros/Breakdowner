/*
  ==============================================================================

    NEASlider.h
    Created: 13 Dec 2021 5:44:26pm
    Author:  Wateo

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class ImageKnob : public juce::Slider
{
public:
    ImageKnob(juce::Image& image, const int numFrames, const bool stripIsHorizontal):
        Slider(),
        filmStrip(image),
        totalNumFrames(numFrames),
        isHorizontal(stripIsHorizontal),
        frameHeigth(0),
        frameWidth(0)
    {
        filmStrip.duplicateIfShared();

        setTextBoxStyle(NoTextBox, 0, 0, 0);

        if (isHorizontal)
        {
            frameHeigth = filmStrip.getHeight();
            frameWidth = filmStrip.getWidth() / totalNumFrames;
        }
        else
        {
            frameHeigth = filmStrip.getHeight() / totalNumFrames;
            frameWidth = filmStrip.getWidth();
        }
    }

    void paint(juce::Graphics& g) override
    {

        const juce::Image imageToPlace = filmStrip;

        const int value = (getValue() - getMinimum()) / (getMaximum() - getMinimum()) * (totalNumFrames - 1);

        if (isHorizontal)
        {
            g.drawImage(imageToPlace, 0, 0, getWidth(), getHeight(),
                value * frameWidth, 0, frameWidth, frameHeigth);
        }
        else
        {
            g.drawImage(imageToPlace, 0, 0, getWidth(), getHeight(),
                0, value * frameHeigth, frameWidth, frameHeigth);
        }
    }


private:

    juce::Image filmStrip, desaturatedImage;
    juce::String nameLabel, unitsLabel;
    bool nameLabelActive, unitsLabelActive;
    const int totalNumFrames;
    const bool isHorizontal;
    int frameWidth, frameHeigth;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ImageKnob)
};

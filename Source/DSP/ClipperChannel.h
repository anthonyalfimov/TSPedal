/*
  ==============================================================================

    ClipperChannel.h
    Created: 6 Feb 2021 2:26:49pm
    Author:  Hack Audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DspChannel.h"

class ClipperChannel  : public DspChannel
{
public:
    ClipperChannel() = default;

//==============================================================================
    void setState (float drive);

//==============================================================================
    void prepare (double sampleRate, int blockSize) override;
    void reset() override;
    void process (const float* inAudio, float* outAudio,
                  int numSamplesToRender) override;

private:
    SmoothedValue<float> mDriveSmoothed;

//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ClipperChannel)
};

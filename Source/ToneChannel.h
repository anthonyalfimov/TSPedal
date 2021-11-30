/*
  ==============================================================================

    ToneChannel.h
    Created: 6 Feb 2021 1:59:16pm
    Author:  Hack Audio

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DspChannel.h"

class ToneChannel  : public DspChannel
{
public:
    ToneChannel() = default;

//==============================================================================
    void setState (float tone, float output);

//==============================================================================
    void prepare (double sampleRate, int blockSize) override;
    void reset() override;
    void process (const float* inAudio, float* outAudio,
                  int numSamplesToRender) override;

private:
    SmoothedValue<float> mToneSmoothed;
    SmoothedValue<float> mOutputSmoothed;

//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToneChannel)
};

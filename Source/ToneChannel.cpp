/*
  ==============================================================================

    ToneChannel.cpp
    Created: 6 Feb 2021 1:59:16pm
    Author:  Hack Audio

  ==============================================================================
*/

#include "ToneChannel.h"

void ToneChannel::setState (float tone, float output)
{
    mToneSmoothed.setTargetValue (tone);
    mOutputSmoothed.setTargetValue (output);
}

//==============================================================================
void ToneChannel::prepare (double sampleRate, int blockSize)
{
    DspChannel::prepare (sampleRate, blockSize);
    reset();
}

void ToneChannel::reset()
{
    // Reset smoothed parameters
    mToneSmoothed.reset (mSampleRate, 0.05f);
    mOutputSmoothed.reset (mSampleRate, 0.05f);
}

void ToneChannel::process (const float* inAudio, float* outAudio, int numSamplesToRender)
{
    // Block processing
}

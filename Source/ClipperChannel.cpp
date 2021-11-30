/*
  ==============================================================================

    ClipperChannel.cpp
    Created: 6 Feb 2021 2:26:49pm
    Author:  Hack Audio

  ==============================================================================
*/

#include "ClipperChannel.h"

void ClipperChannel::setState (float drive)
{
    mDriveSmoothed.setTargetValue (drive);
}

//==============================================================================
void ClipperChannel::prepare (double sampleRate, int blockSize)
{
    DspChannel::prepare (sampleRate, blockSize);
    reset();
}

void ClipperChannel::reset()
{
    // Reset smoothed parameters
    mDriveSmoothed.reset (mSampleRate, 0.05f);
}

void ClipperChannel::process (const float* inAudio, float* outAudio, int numSamplesToRender)
{
    // Block processing
}



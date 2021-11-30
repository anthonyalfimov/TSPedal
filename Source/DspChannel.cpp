/*
  ==============================================================================

    DspChannel.cpp
    Created: 30 Nov 2021 3:30:30pm
    Author:  Anthony

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DspChannel.h"

void DspChannel::prepare (double sampleRate, int blockSize)
{
    jassert (sampleRate > 0.0);
    jassert (blockSize > 0);

    mSampleRate = sampleRate;
    mBlockSize = blockSize;
}

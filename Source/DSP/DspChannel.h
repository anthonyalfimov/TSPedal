/*
  ==============================================================================

    DspChannel.h
    Created: 30 Nov 2021 3:30:30pm
    Author:  Anthony

  ==============================================================================
*/

#pragma once

// TODO: Consider deriving a base class for circuit-modelling processors
//  This class can handle calculations that are shared between all CM processors

class DspChannel
{
public:
    DspChannel() = default;
    virtual ~DspChannel() = default;

//==============================================================================
    virtual void prepare (double sampleRate, int blockSize);
    virtual void reset() = 0;
    
    virtual void process (const float* inAudio, float* outAudio,
                          int numSamplesToRender) = 0;

protected:
    double mSampleRate = 44100.0;
    int mBlockSize = 0;
};

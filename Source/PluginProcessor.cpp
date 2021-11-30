/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TSPedalAudioProcessor::TSPedalAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    // Initialise DSP modules
    initialiseDSP();
}

TSPedalAudioProcessor::~TSPedalAudioProcessor()
{
}

//==============================================================================
const juce::String TSPedalAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TSPedalAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TSPedalAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TSPedalAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TSPedalAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TSPedalAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TSPedalAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TSPedalAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TSPedalAudioProcessor::getProgramName (int index)
{
    return {};
}

void TSPedalAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TSPedalAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    for (auto clipperChannel : mClipper)
        clipperChannel->prepare (sampleRate, samplesPerBlock);

    for (auto toneChannel : mTone)
        toneChannel->prepare (sampleRate, samplesPerBlock);
}

void TSPedalAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    for (auto clipperChannel : mClipper)
        clipperChannel->reset();

    for (auto toneChannel : mTone)
        toneChannel->reset();
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TSPedalAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // Support mono & stereo layout for output bus
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

   #if ! JucePlugin_IsSynth
    // Input bus should have the same number of channels as the output bus
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void TSPedalAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    const auto numSamples = buffer.getNumSamples();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // Processing%
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // TODO: Check the order of processing!
        mClipper[channel]->process (channelData, channelData, numSamples);
        mTone[channel]->process (channelData, channelData, numSamples);
    }
}

//==============================================================================
bool TSPedalAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TSPedalAudioProcessor::createEditor()
{
    return new TSPedalAudioProcessorEditor (*this);
}

//==============================================================================
void TSPedalAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void TSPedalAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
void TSPedalAudioProcessor::initialiseDSP()
{
    const auto totalNumInputChannels = getTotalNumInputChannels();

    // Create DSP channels
    for (int i = 0; i < totalNumInputChannels; ++i)
    {
        mClipper.add (std::make_unique<ClipperChannel>());
        mTone.add (std::make_unique<ToneChannel>());
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new TSPedalAudioProcessor();
}

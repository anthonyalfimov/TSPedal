/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TSPedalAudioProcessorEditor::TSPedalAudioProcessorEditor (TSPedalAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Set up Editor attributes
    setSize (275, 485);
}

TSPedalAudioProcessorEditor::~TSPedalAudioProcessorEditor()
{
    // Release the look and feel
    setLookAndFeel (nullptr);
    LookAndFeel::setDefaultLookAndFeel (nullptr);
}

//==============================================================================
void TSPedalAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("WIP", getLocalBounds(), juce::Justification::centred, 1.0f);
}

void TSPedalAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}


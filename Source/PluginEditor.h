/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/

class AudioFileComponent : public Label
{
public:
    void mouseDrag(const MouseEvent& event) override;
};

class NewProjectAudioProcessorEditor  : public AudioProcessorEditor,
                                        public DragAndDropContainer
{
public:
    NewProjectAudioProcessorEditor (NewProjectAudioProcessor&);
    ~NewProjectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void downloadVideo();


private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& processor;
    
    Label titleLabel;
    Label inputLabel;
    Label inputText;
    TextButton downloadButton   { "Download audio from YouTube" };
    TextButton dragButton { "Drag audio" };
    AudioFileComponent audioFileComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};


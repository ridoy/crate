/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include <filesystem>
#include <regex>
#include <iostream>
#include <algorithm>

//==============================================================================
/**
*/

class AudioFileComponent : public Label
{
public:
    String currentAudioFile = "/Users/ridoymajumdar/Documents/JUCE/extras/AudioPluginHost/Builds/MacOSX/build/Debug/test.mp3";
    void setCurrentAudioFile(String filename);
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
    TextEditor inputText;
    TextEditor debugText;
    TextButton downloadButton   { "Mownload audio from YouTube" };
    TextButton dragButton { "Drag audio" };
    AudioFileComponent audioFileComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NewProjectAudioProcessorEditor)
};


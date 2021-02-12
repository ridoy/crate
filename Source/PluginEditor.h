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
#include <thread>
#include "Waveform.h"
//==============================================================================
/**
 */

class AudioFileComponent : public Label
{
public:
    AudioFileComponent() {
        //addAndMakeVisible(waveform);
    }
    
    String currentAudioFile;
    void setCurrentAudioFile(String filename);
    void mouseDrag(const MouseEvent& event) override;
    
    void resized() override {
        waveform.setBounds(0, 0, getWidth(), getHeight());
    }
    
    Waveform waveform;
private:
//    Waveform waveform;
};

class CrateDigger  : public AudioProcessorEditor,
public DragAndDropContainer
{
public:
    CrateDigger (NewProjectAudioProcessor&);
    ~CrateDigger();
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    void downloadVideo();
    void setText();
    void runYtdlChildProcess();
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NewProjectAudioProcessor& processor;
    TextButton header;
    TextEditor searchBarInput;
    TextButton downloadButton   { "Download" };

    Label titleLabel;
    Label inputLabel;
    TextEditor inputText;
    TextButton debugText;
    TextButton dragButton { "Drag audio" };
    AudioFileComponent audioFileComponent;
    
    Waveform waveformComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrateDigger)
};


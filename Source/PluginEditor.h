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
    String currentAudioFile;
    void setCurrentAudioFile(String filename);
    void mouseDrag(const MouseEvent& event) override;
    
private:
};

//==============================================================================

class CrateDigger  : public AudioProcessorEditor,
public DragAndDropContainer
{
public:
    CrateDigger (NewProjectAudioProcessor&);
    ~CrateDigger();
    
    void paint (Graphics&) override;
    void resized() override;
    void downloadVideo();
    void setText();
    void runYtdlChildProcess();
    
private:
    NewProjectAudioProcessor& processor;

    Label namePlugin;
    TextEditor searchBarInput, bar;
    TextButton downloadButton{"Download"};
    Label statusLabel;
    Label debugText;
    Waveform waveformComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrateDigger)
};


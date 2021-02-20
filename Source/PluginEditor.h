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
#include "LibrariesManager.cpp"

class CrateDigger  : public AudioProcessorEditor,
public DragAndDropContainer
{
public:
    CrateDigger (NewProjectAudioProcessor&);
    ~CrateDigger();
    
    void paint (Graphics&) override;
    void resized() override;
    void downloadVideo();
    void processDownload();
    
private:
    NewProjectAudioProcessor& processor;

    Label namePlugin;
    TextEditor searchBarInput, bar;
    TextButton downloadButton{"Download"};
    Label statusLabel;
    Label debugText;
    Waveform waveformComponent;
    
    File downloadsFolder;
    LibrariesManager librariesManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrateDigger)
};


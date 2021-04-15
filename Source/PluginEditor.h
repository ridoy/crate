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
#include "LibrariesManager.h"
#include "PathsWindow.h"

class CrateDigger  : public AudioProcessorEditor,
public DragAndDropContainer
{
public:
    CrateDigger (NewProjectAudioProcessor&);
    ~CrateDigger();
    
    void paint (Graphics&) override;
    void resized() override;
    void checkPathFiles();
    void downloadVideo();
    void processDownload();
    void setPaths();
    void updateLibrariesPaths();
    void updateYoutubedl();
    
private:
    NewProjectAudioProcessor& processor;

    Label namePlugin;
    TextEditor searchBarInput;
    TextButton downloadButton{"Download"};
    Label statusLabel;
    Label debugText;
    Waveform waveformComponent;
    
    String downloadsFolder;
    LibrariesManager librariesManager;
    
    String filePath;
    String ffmpegPathForChildProcess;
    
    PathsWindow pathsWindow;
    TextButton setPathsButton{"Set Paths"};
    
    TextButton updateButton{"Update"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CrateDigger)
};


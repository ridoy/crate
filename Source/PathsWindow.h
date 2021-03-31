/*
  ==============================================================================

    PathsWindow.h
    Created: 20 Feb 2021 4:49:12pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "LibrariesManager.h"


class PathsWindow : public Component, public Button::Listener {
public:
    PathsWindow();
    ~PathsWindow();
    
    void paint(Graphics&) override;
    void resized() override;
    
    void dismissWindow();
    void buttonClicked(Button*) override;
    
    void setLibrariesPaths(String& _youtubedlPath, String& _ffmpegPath, String& _downloadsPath);
    String getYotubedlPath();
    String getFfmpegPath();
    String getDownloadsPath();
    
    
private:
    Label instructionLabel, youtubedlPathLabel, ffmpegPathLabel, downloadsPathLabel;
    TextEditor youtubedlPathEditor, ffmpegPathEditor, downloadsPathEditor;
    TextButton  goBackButton{"Go Back"} ,browseYtdlButton {"Browse..."}, browseFfmpegButton{"Browse..."}, browseDownloadsButton {"Browse..."};
    
    String youtubedlPath, ffmpegPath, downloadsPath;
    
    LibrariesManager librariesManager;
    
    int flagsForFiles = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles; //Flags for chooser async
    int flagsForDirectories = FileBrowserComponent::openMode | FileBrowserComponent::canSelectDirectories; //Flags for chooser async
    
    std::unique_ptr<FileChooser> chooser;
};

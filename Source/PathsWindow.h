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
    
    void setLibrariesPaths(String& youtubedlPath, String& ffmpegPath);
    String getYotubedlPath();
    String getFfmpegPath();
    
    
private:
    Label instructionLabel, youtubedlPathLabel, ffmpegPathLabel;
    TextEditor youtubedlPathEditor, ffmpegPathEditor;
    TextButton  goBackButton{"Go Back"} ,browseYtdlButton {"Browse..."}, browseFfmpegButton{"Browse..."};
    
    String youtubedlPath, ffmpegPath;
    
    LibrariesManager librariesManager;
    
    int flags = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;
    std::unique_ptr<FileChooser> chooser;
};

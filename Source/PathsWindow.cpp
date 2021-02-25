/*
  ==============================================================================

    PathsWindow.cpp
    Created: 20 Feb 2021 4:49:12pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#include "PathsWindow.h"

PathsWindow::PathsWindow() {
    
    //Set Labels
    addAndMakeVisible(instructionLabel);
    instructionLabel.setText("Set Libraries Paths", dontSendNotification);
    instructionLabel.setFont(Font(18.0f, Font::FontStyleFlags::bold));
    instructionLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(youtubedlPathLabel);
    youtubedlPathLabel.setText("Youtube-dl Library Path:", dontSendNotification);
    addAndMakeVisible(ffmpegPathLabel);
    ffmpegPathLabel.setText("Ffmpeg Library Path:", dontSendNotification);

    //Set Text Editors
    youtubedlPathEditor.setColour(TextEditor::textColourId, Colours::whitesmoke);
    addAndMakeVisible(youtubedlPathEditor);
    ffmpegPathEditor.setColour(TextEditor::textColourId, Colours::whitesmoke);
    addAndMakeVisible(ffmpegPathEditor);
    
    //Set Button
    addAndMakeVisible(browseYtdlButton);
    browseYtdlButton.setAlpha(1.0f);
    browseYtdlButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    browseYtdlButton.addListener(this);
    addAndMakeVisible(browseFfmpegButton);
    browseFfmpegButton.setAlpha(1.0f);
    browseFfmpegButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    browseFfmpegButton.addListener(this);
    addAndMakeVisible(goBackButton);
    goBackButton.setAlpha(1.0f);
    goBackButton.setColour(TextButton::buttonColourId, Colours::grey);
    goBackButton.addListener(this);
}

PathsWindow::~PathsWindow() {
    
}

void PathsWindow::paint(Graphics& g) {
    g.fillAll(Colours::royalblue);
}

void PathsWindow::resized() {
    instructionLabel.setBoundsRelative(0.0f, 0.05f, 1.0f, 0.1f);
    youtubedlPathLabel.setBoundsRelative(0.05f, 0.2f, 0.8f, 0.1f);
    ffmpegPathLabel.setBoundsRelative(0.05f, 0.5f, 0.8f, 0.1f);
    
    youtubedlPathEditor.setBoundsRelative(0.1f, 0.3f, 0.8f, 0.1f);
    ffmpegPathEditor.setBoundsRelative(0.1f, 0.6f, 0.8f, 0.1f);

    browseYtdlButton.setSize(80, 20);
    browseYtdlButton.setCentreRelative(0.5f, 0.45f);
    browseFfmpegButton.setSize(80, 20);
    browseFfmpegButton.setCentreRelative(0.5f, 0.75f);
    goBackButton.setSize(100, 30);
    goBackButton.setCentreRelative(0.5f, 0.9f);
    
    
}

void PathsWindow::dismissWindow() {
    setVisible(false);
};

void PathsWindow::buttonClicked(Button* buttonClicked) {
    if(buttonClicked == &goBackButton) {
        youtubedlPath = youtubedlPathEditor.getText();
        ffmpegPath = ffmpegPathEditor.getText();
        dismissWindow();
    }
    
    if(buttonClicked == &browseYtdlButton) {
        FileChooser chooser("Find Youtube-dl Location", File::getSpecialLocation (File::userHomeDirectory), "");
        if (chooser.browseForFileToOpen()) {
            File newLocationPath(chooser.getResult());
            youtubedlPath = newLocationPath.getFullPathName();
            youtubedlPathEditor.setText(youtubedlPath, dontSendNotification);
        }
    }
    
    if(buttonClicked == &browseFfmpegButton) {
        FileChooser chooser("Find Ffmpeg Location", File::getSpecialLocation (File::userHomeDirectory), "");
        if(chooser.browseForFileToOpen()) {
            File newLocationPath(chooser.getResult());
            ffmpegPath = newLocationPath.getFullPathName();
            ffmpegPathEditor.setText(ffmpegPath, dontSendNotification);
        }
    }
}

void PathsWindow::setLibrariesPaths(String& _youtubedlPath, String& _ffmpegPath) {
    youtubedlPath = _youtubedlPath;
    ffmpegPath = _ffmpegPath;
    
    youtubedlPathEditor.setText(youtubedlPath, dontSendNotification);
    ffmpegPathEditor.setText(ffmpegPath, dontSendNotification);
}

String PathsWindow::getYotubedlPath() {
    return youtubedlPath;
}

String PathsWindow::getFfmpegPath() {
    return ffmpegPath;
}

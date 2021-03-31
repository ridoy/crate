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
    instructionLabel.setText("Set Paths", dontSendNotification);
    instructionLabel.setFont(Font(19.0f, Font::FontStyleFlags::bold));
    instructionLabel.setJustificationType(Justification::centred);
    
    addAndMakeVisible(youtubedlPathLabel);
    youtubedlPathLabel.setText("Youtube-dl Library Path:", dontSendNotification);
    
    addAndMakeVisible(ffmpegPathLabel);
    ffmpegPathLabel.setText("Ffmpeg Library Path:", dontSendNotification);
    
    addAndMakeVisible(downloadsPathLabel);
    downloadsPathLabel.setText("Downloads Folder Path", dontSendNotification);

    //Set Text Editors
    youtubedlPathEditor.setColour(TextEditor::textColourId, Colours::whitesmoke);
    addAndMakeVisible(youtubedlPathEditor);
    
    ffmpegPathEditor.setColour(TextEditor::textColourId, Colours::whitesmoke);
    addAndMakeVisible(ffmpegPathEditor);
    
    downloadsPathEditor.setColour(TextEditor::textColourId, Colours::whitesmoke);
    addAndMakeVisible(downloadsPathEditor);
    
    
    //Set Buttons
    addAndMakeVisible(browseYtdlButton);
    browseYtdlButton.setAlpha(1.0f);
    browseYtdlButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    browseYtdlButton.addListener(this);

    addAndMakeVisible(browseFfmpegButton);
    browseFfmpegButton.setAlpha(1.0f);
    browseFfmpegButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    browseFfmpegButton.addListener(this);
    
    addAndMakeVisible(browseDownloadsButton);
    browseDownloadsButton.setAlpha(1.0f);
    browseDownloadsButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    browseDownloadsButton.addListener(this);
    
    addAndMakeVisible(goBackButton);
    goBackButton.setAlpha(1.0f);
    goBackButton.setColour(TextButton::buttonColourId, Colours::grey);
    goBackButton.addListener(this);
    
    //==============================================================================
    //Code if running in Windows
//    if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0) {
//        //Set Labels
//        addAndMakeVisible(ffmpegPathLabel);
//        ffmpegPathLabel.setText("Ffmpeg Library Path:", dontSendNotification);
//
//        //Set Text Editors
//        ffmpegPathEditor.setColour(TextEditor::textColourId, Colours::whitesmoke);
//        addAndMakeVisible(ffmpegPathEditor);
//
//        //Set Button
//        addAndMakeVisible(browseFfmpegButton);
//        browseFfmpegButton.setAlpha(1.0f);
//        browseFfmpegButton.setColour(TextButton::buttonColourId, Colours::darkblue);
//        browseFfmpegButton.addListener(this);
//    }
    
}

PathsWindow::~PathsWindow() {
    
}

void PathsWindow::paint(Graphics& g) {
    g.fillAll(Colours::royalblue);
}

void PathsWindow::resized() {
    instructionLabel.setBoundsRelative(0.0f, 0.05f, 1.0f, 0.1f);
    youtubedlPathLabel.setBoundsRelative(0.05f, 0.2f, 0.8f, 0.1f);
    ffmpegPathLabel.setBoundsRelative(0.05f, 0.4f, 0.8f, 0.1f);
    downloadsPathLabel.setBoundsRelative(0.05f, 0.6f, 0.8f, 0.1f);
    
    youtubedlPathEditor.setBoundsRelative(0.05f, 0.3f, 0.65f, 0.1f);
    ffmpegPathEditor.setBoundsRelative(0.05f, 0.5f, 0.65f, 0.1f);
    downloadsPathEditor.setBoundsRelative(0.05f, 0.7f, 0.65f, 0.1f);
    
    browseYtdlButton.setBoundsRelative(0.72f, 0.3f, 0.22f, 0.1f);
    browseFfmpegButton.setBoundsRelative(0.72f, 0.5f, 0.22f, 0.1f);
    browseDownloadsButton.setBoundsRelative(0.72f, 0.7f, 0.22f, 0.1f);

    goBackButton.setSize(100, 30);
    goBackButton.setCentreRelative(0.5f, 0.9f);
    
    //==============================================================================
    //Code if running in Windows
//    if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0) {
//        ffmpegPathLabel.setBoundsRelative(0.05f, 0.5f, 0.8f, 0.1f);
//        ffmpegPathEditor.setBoundsRelative(0.05f, 0.6f, 0.9f, 0.1f);
//        browseFfmpegButton.setSize(80, 20);
//        browseFfmpegButton.setCentreRelative(0.5f, 0.75f);
//    }
   
}

void PathsWindow::dismissWindow() {
    setVisible(false);
};

void PathsWindow::buttonClicked(Button* buttonClicked) {
    //Go Back Button Listener Action
    if(buttonClicked == &goBackButton) {
        if (youtubedlPathEditor.getText().isNotEmpty())
            youtubedlPath = youtubedlPathEditor.getText();
        
        if (ffmpegPathEditor.getText().isNotEmpty())
            ffmpegPath = ffmpegPathEditor.getText();
        
        if (downloadsPathEditor.getText().isNotEmpty())
            downloadsPath = downloadsPathEditor.getText();
        
        dismissWindow();
    }
    
    //Browse Youtube-dl Button Listener Action
    if(buttonClicked == &browseYtdlButton) {
        chooser.reset (new FileChooser ("Find Youtube-dl Location", File::getSpecialLocation (File::userHomeDirectory), ""));
        chooser->launchAsync (flagsForFiles, [=] (const FileChooser& fc)
            {
                File newLocationPath(fc.getResult());
            
                if (newLocationPath.getFullPathName().isNotEmpty()) {
                    youtubedlPath = newLocationPath.getFullPathName();
                    youtubedlPathEditor.setText(youtubedlPath, dontSendNotification);
            }
        });
      
    }
    
    //Browse Fffmpeg Button Listener Action
    if(buttonClicked == &browseFfmpegButton) {
        chooser.reset(new FileChooser("Find Ffmpeg Location", File::getSpecialLocation(File::userHomeDirectory), ""));
        chooser->launchAsync(flagsForFiles, [=](const FileChooser& fc)
            {
                File newLocationPath(fc.getResult());

                if (newLocationPath.getFullPathName().isNotEmpty()) 
                {
                    ffmpegPath = newLocationPath.getFullPathName();
                    ffmpegPathEditor.setText(ffmpegPath, dontSendNotification);
                }
        });
        
    }
    
    //Browse Downloads Folder Button Listener Action
    if(buttonClicked == &browseDownloadsButton) {
        chooser.reset (new FileChooser ("Find Downloads Folder Location", File::getSpecialLocation (File::userHomeDirectory), ""));
        chooser->launchAsync (flagsForDirectories, [=] (const FileChooser& fc)
            {
                File newLocationPath(fc.getResult());
            
                if (newLocationPath.getFullPathName().isNotEmpty()) {
                    downloadsPath = newLocationPath.getFullPathName();
                    downloadsPathEditor.setText(downloadsPath, dontSendNotification);
                }
        });
      
    }
}

void PathsWindow::setLibrariesPaths(String& _youtubedlPath, String& _ffmpegPath, String& _downloadsPath)
    {
    youtubedlPath = _youtubedlPath;
    ffmpegPath = _ffmpegPath;
    downloadsPath = _downloadsPath;
    
    youtubedlPathEditor.setText(youtubedlPath, dontSendNotification);

    if (ffmpegPath.isQuotedString()) {
        String ffmpegPathUnquoted = ffmpegPath.unquoted();
        ffmpegPathEditor.setText(ffmpegPathUnquoted, dontSendNotification);
    }
    else
        ffmpegPathEditor.setText(ffmpegPath, dontSendNotification);
    
    downloadsPathEditor.setText(downloadsPath, dontSendNotification);
}

String PathsWindow::getYotubedlPath() {
    return youtubedlPath;
}

String PathsWindow::getFfmpegPath() {
    return ffmpegPath;
}

String PathsWindow::getDownloadsPath() {
    return downloadsPath;
}

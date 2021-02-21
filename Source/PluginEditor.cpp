/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <thread>
//==============================================================================
CrateDigger::CrateDigger (NewProjectAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    //Title Plugin Name
    namePlugin.setText("CrateDigger v0.1", dontSendNotification);
    namePlugin.setColour(Label::ColourIds::textColourId, Colours::darkblue);
    namePlugin.setFont(Font(40.0f, Font::FontStyleFlags::bold));
    namePlugin.setJustificationType(Justification::centred);
    addAndMakeVisible(namePlugin);

    //SearchBar Input
    searchBarInput.setMultiLine(false);
    searchBarInput.setTextToShowWhenEmpty("Enter Youtube URL", Colours::whitesmoke);
    searchBarInput.setColour(TextEditor::ColourIds::backgroundColourId, Colours::lightslategrey);
    searchBarInput.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    searchBarInput.setColour (TextEditor::shadowColourId,  Colour (0x16000000));
    addAndMakeVisible(searchBarInput);
    
    //Download Button
    downloadButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    downloadButton.setAlpha(0.9f);
    addAndMakeVisible(downloadButton);
    downloadButton.onClick = [this]() { return this->downloadVideo(); };
    
    //Set Paths Button
    setPathsButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    setPathsButton.setAlpha(0.7f);
    addAndMakeVisible(setPathsButton);
    setPathsButton.onClick = [this]() { return this->setPaths(); };
    
    //Status Label Text
    statusLabel.setText("", dontSendNotification);
    statusLabel.setFont(Font(15.0f, Font::FontStyleFlags::bold));
    statusLabel.setColour(Label::ColourIds::textColourId, Colours::dimgrey);
    statusLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(statusLabel);
    
    //Debug Label Text
    debugText.setText("", dontSendNotification);
    debugText.setColour(Label::ColourIds::textColourId, Colours::dimgrey);
    debugText.setJustificationType(Justification::centred);
    addAndMakeVisible(debugText);
    
    checkPathFiles();
                    
    downloadsFolder = LibrariesManager::getFolderDirectory(LibrariesManager::Folder::Downloads);
    librariesManager.getLibrariesPaths();
    
    addAndMakeVisible(waveformComponent);
    
    addAndMakeVisible(pathsWindow);
    pathsWindow.setVisible(false);
    pathsWindow.setLibrariesPaths(librariesManager.youtubedlPath, librariesManager.ffmpegPath);
    
    setSize (400, 400);
}

CrateDigger::~CrateDigger()
{
}

void CrateDigger::paint (Graphics& g)
{
    g.fillAll(Colours::white);
    
    pathsWindow.setAlpha(0.95f);
    
}

void CrateDigger::resized()
{
    namePlugin.setBoundsRelative(0.0f, 0.0f, 1.0f, 0.2f);
    
    searchBarInput.setBoundsRelative(0.1f, 0.25f, 0.8f, 0.07f);
  
    downloadButton.setBoundsRelative(0.55f, 0.35f, 0.2f, 0.1f);
    
    setPathsButton.setBoundsRelative(0.25f, 0.35f, 0.2f, 0.1f);
    
    waveformComponent.setBoundsRelative(0.05f, 0.5f, 0.90f, 0.2f);
    
    statusLabel.setBoundsRelative(0.05f, 0.72f, 0.9f, 0.05f);
    
    debugText.setBoundsRelative(0.05f, 0.78f, 0.9f, 0.15f);
    
    pathsWindow.setBoundsRelative(0.1f, 0.1f, 0.8f, 0.8f);
}

void CrateDigger::checkPathFiles() {
    bool pathFileExists = LibrariesManager::getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("youtube-dl_Path.txt").exists();
    if (!pathFileExists) {
        LibrariesManager::createPathFiles("youtube-dl");
    }
    
    pathFileExists = LibrariesManager::getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("ffmpeg_Path.txt").exists();
    if (!pathFileExists) {
        LibrariesManager::createPathFiles("ffmpeg");
    }
}

void CrateDigger::downloadVideo()
{
    //Update Libraries paths if changed
    if ((librariesManager.youtubedlPath != pathsWindow.getYotubedlPath()) || (librariesManager.ffmpegPath != pathsWindow.getFfmpegPath())) {
        librariesManager.updateLibrariesPaths(pathsWindow.getYotubedlPath(), pathsWindow.getFfmpegPath());
    }
    
    File youtubedlLibrary(librariesManager.youtubedlPath);
    File ffmpegLibrary(librariesManager.ffmpegPath);
    
    //Check if libraries exists and process or show alert if not
    bool youtubedlLibraryExists = youtubedlLibrary.exists();
    bool ffmpegLibraryExists = ffmpegLibrary.exists();
    int librariesExistsCase = 0;
    
    if (youtubedlLibraryExists == true && ffmpegLibraryExists == true)
        librariesExistsCase = 0;
    else if (youtubedlLibraryExists == false && ffmpegLibraryExists == false)
        librariesExistsCase = 1;
    else if (youtubedlLibraryExists == true && ffmpegLibraryExists == false)
        librariesExistsCase = 2;
    else if (youtubedlLibraryExists == false && ffmpegLibraryExists == true)
        librariesExistsCase = 3;
    
    switch (librariesExistsCase) {
        case 0:
            processDownload();
            break;
        case 1:
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Youtube-dl and ffmpeg libraries found", "Check Youtube-dl and ffmpeg libraries libraries paths", "Close", nullptr);
            break;
        case 2:
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Ffmpeg library found", "Check Ffmpeg library path", "Close", nullptr);
            break;
        case 3:
            AlertWindow::showMessageBox(AlertWindow::WarningIcon, "No Youtube-dl library found", "Check Youtube-dl library path", "Close", nullptr);
            break;
            
        default:
            processDownload();
            break;
    }
}

void CrateDigger::processDownload() {
    juce::ChildProcess ytdlChildProcess;
    String youtubeUrl = searchBarInput.getTextValue().toString();
    
    //Process download
    String downloadsLocationString = downloadsFolder.getFullPathName();
    String ytdlCommand = librariesManager.youtubedlPath + " --output " + downloadsLocationString + "/%(title)s.%(ext)s --extract-audio --audio-format mp3 --ffmpeg-location " + librariesManager.ffmpegPath + " " + youtubeUrl;
    ytdlChildProcess.start(ytdlCommand, 0x03);
    ytdlChildProcess.waitForProcessToFinish(30000);
    
    String ytdlCommandFilename = librariesManager.youtubedlPath + " --get-filename --output " + downloadsLocationString + "/%(title)s.mp3 --extract-audio --audio-format mp3 --ffmpeg-location " + librariesManager.ffmpegPath + " " + youtubeUrl;
    ytdlChildProcess.start(ytdlCommandFilename, 0x03);
    
    String filePath = ytdlChildProcess.readAllProcessOutput();
    filePath = filePath.replace("\n", "");
    filePath = filePath.replace("\r", "");
    
    //Log to plugin result from library
    if (filePath.startsWith("Usage") || filePath.startsWith("WARNING") || filePath.startsWith("ERROR")) {
        waveformComponent.resetThumbnail();
        statusLabel.setText("Download Error", dontSendNotification);
        debugText.setText(filePath, dontSendNotification);
    } else {
        waveformComponent.loadFile(filePath);
        waveformComponent.setCurrentAudioFile(filePath);
        statusLabel.setText("Done loading, drag waveform into your DAW", dontSendNotification);
        debugText.setText(filePath, dontSendNotification);
    }
}

void CrateDigger::setPaths() {
    pathsWindow.setVisible(true);
}

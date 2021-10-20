/*
 ==============================================================================
 
 This file was auto-generated!
 
 It contains the basic framework code for a JUCE plugin editor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <thread>
#include <regex>


Crate::Crate (NewProjectAudioProcessor& p)
: AudioProcessorEditor (&p), processor (p)
{
    //Title Plugin Name
    namePlugin.setText("Crate v1.1", dontSendNotification);
    namePlugin.setColour(Label::ColourIds::textColourId, Colours::darkblue);
    namePlugin.setFont(Font(40.0f, Font::FontStyleFlags::bold));
    namePlugin.setJustificationType(Justification::centred);
    addAndMakeVisible(namePlugin);

    //SearchBar Input
    searchBarInput.setMultiLine(false);
    searchBarInput.setText(processor.getTextEditorsStates(0));
    searchBarInput.setTextToShowWhenEmpty("Enter Youtube URL", Colours::whitesmoke);
    searchBarInput.setColour(TextEditor::ColourIds::backgroundColourId, Colours::lightslategrey);
    searchBarInput.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    searchBarInput.setColour (TextEditor::shadowColourId,  Colour (0x16000000));
    addAndMakeVisible(searchBarInput);

    //Update Button
    updateButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    updateButton.setAlpha(0.9f);
    addAndMakeVisible(updateButton);
    updateButton.onClick = [this]() { return this->updateYoutubedl(); };
    
    //Download Button
    downloadButton.setEnabled(true);
    downloadButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    downloadButton.setAlpha(0.9f);
    addAndMakeVisible(downloadButton);

    downloadButton.onClick = [this]
        {
            isDownloading = true;
            progress = "0.0%";
            downloadButton.setButtonText(progress);
            downloadButton.setEnabled(false);

            auto sp = SafePointer<Crate>(this);
            Thread::launch ([ sp ] () mutable
                            {
                                sp->downloadVideo(sp, sp->progress);
                                MessageManager::getInstance()->callAsync ([sp] () mutable
                                                                          {
                                                                              if (sp != nullptr)
                                                                                  sp->downloadCompleteCallback();
                                                                          });
                            });
        };
    //Set Paths Button
    setPathsButton.setColour(TextButton::buttonColourId, Colours::darkblue);
//    setPathsButton.setAlpha(0.7f);
    addAndMakeVisible(setPathsButton);
    setPathsButton.onClick = [this]() { return this->setPaths(); };
    
    //Status Label Text
    statusLabel.setText(processor.getTextEditorsStates(1), dontSendNotification);
    statusLabel.setFont(Font(15.0f, Font::FontStyleFlags::bold));
    statusLabel.setColour(Label::ColourIds::textColourId, Colours::dimgrey);
    statusLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(statusLabel);
    
    //Debug Label Text
    debugText.setText(processor.getTextEditorsStates(2), dontSendNotification);
    debugText.setColour(Label::ColourIds::textColourId, Colours::dimgrey);
    debugText.setJustificationType(Justification::centred);
    addAndMakeVisible(debugText);
    
    //Check Paths
    checkPathFiles();
    librariesManager.getLocationsPaths();
    
    //Waveform Component
    waveformComponent.loadFile(processor.getWaveformStatus());
    waveformComponent.setCurrentAudioFile(processor.getWaveformStatus());
    addAndMakeVisible(waveformComponent);
    
    //Set Paths Window
    addAndMakeVisible(pathsWindow);
    pathsWindow.setVisible(false);
    pathsWindow.setLibrariesPaths(librariesManager.youtubedlPath, librariesManager.ffmpegPath, librariesManager.downloadsPath);
    
    setSize (400, 400);
}

Crate::~Crate()
{
    if (!(searchBarInput.isEmpty()))
        processor.setTextEditorsStates(0, searchBarInput.getText());
    
    if (statusLabel.getText().isNotEmpty())
        processor.setTextEditorsStates(1, statusLabel.getText());
    
    if (debugText.getText().isNotEmpty())
        processor.setTextEditorsStates(2, debugText.getText());
    
    if (filePath.isNotEmpty())
        processor.setWaveformStatus(filePath);
}

void Crate::paint (Graphics& g)
{
    g.fillAll(Colours::white);
    
    pathsWindow.setAlpha(0.95f);
    if (isDownloading) {
        downloadButton.setButtonText(progress);
    }
}

void Crate::resized()
{
    namePlugin.setBoundsRelative(0.0f, 0.0f, 1.0f, 0.2f);
    
    searchBarInput.setBoundsRelative(0.1f, 0.25f, 0.8f, 0.07f);
    
    updateButton.setBoundsRelative(0.1f, 0.35f, 0.2f, 0.1f);
    setPathsButton.setBoundsRelative(0.35f, 0.35f, 0.2f, 0.1f);
    downloadButton.setBoundsRelative(0.6f, 0.35f, 0.3f, 0.1f);
    
    waveformComponent.setBoundsRelative(0.05f, 0.5f, 0.90f, 0.2f);
    
    statusLabel.setBoundsRelative(0.05f, 0.72f, 0.9f, 0.05f);
    
    debugText.setBoundsRelative(0.05f, 0.78f, 0.9f, 0.15f);
    
    pathsWindow.setBoundsRelative(0.1f, 0.1f, 0.8f, 0.8f);

}

void Crate::checkPathFiles() {
    //Code if running in macOS
    if ((SystemStats::getOperatingSystemType() & SystemStats::MacOSX) != 0) {
        bool pathFileExists = LibrariesManager::getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("youtube-dl_Path.txt").exists();
        if (!pathFileExists) {
            LibrariesManager::createPathFiles("youtube-dl");
        }
        
        pathFileExists = LibrariesManager::getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("ffmpeg_Path.txt").exists();
        if (!pathFileExists) {
            LibrariesManager::createPathFiles("ffmpeg");
        }
        
        pathFileExists = LibrariesManager::getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("downloads_Path.txt").exists();
        if (!pathFileExists) {
            LibrariesManager::createPathFiles("downloads");
        }
    }
    
    //==============================================================================
    //Code if running in Windows
    if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0) {
        bool pathFileExists = LibrariesManager::getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("youtube-dl_Path.txt").exists();
        if (!pathFileExists) {
            LibrariesManager::createPathFiles("youtube-dl");
        }

        pathFileExists = LibrariesManager::getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("ffmpeg_Path.txt").exists();
        if (!pathFileExists) {
            LibrariesManager::createPathFiles("ffmpeg");
        }
        
        pathFileExists = LibrariesManager::getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("downloads_Path.txt").exists();
        if (!pathFileExists) {
            LibrariesManager::createPathFiles("downloads");
        }
    }
}

void Crate::downloadVideo(Component::SafePointer<Crate> component, String& progress)
{
    Logger::getCurrentLogger()->writeToLog("At downloadVideo()");

    //Code if running in macOS
    if ((SystemStats::getOperatingSystemType() & SystemStats::MacOSX) != 0) {
        
        //Update Libraries paths if changed
        updateLibrariesPaths();
        
        File youtubedlLibrary(librariesManager.youtubedlPath);
        File ffmpegLibrary(librariesManager.ffmpegPath);
        downloadsFolder = librariesManager.downloadsPath;
        
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
                processDownload(component, progress);
                break;
            case 1:
                AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "No Youtube-dl and ffmpeg libraries found", "Check Youtube-dl and ffmpeg libraries libraries paths", "Close", nullptr);
                break;
            case 2:
                AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "No Ffmpeg library found", "Check Ffmpeg library path", "Close", nullptr);
                break;
            case 3:
                AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "No Youtube-dl library found", "Check Youtube-dl library path", "Close", nullptr);
                break;
                
            default:
                processDownload(component, progress);
                break;
        }
    }

    //==============================================================================
    //Code if running in Windows
    if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0) {
        
        //Update Libraries paths if changed
        updateLibrariesPaths();
        
        File youtubedlLibrary(librariesManager.youtubedlPath);
        File ffmpegLibrary(librariesManager.ffmpegPath);
        downloadsFolder = librariesManager.downloadsPath;
        
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
                processDownload(component, progress);
                break;
            case 1:
                AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "No Youtube-dl and ffmpeg libraries found", "Check Youtube-dl and ffmpeg libraries libraries paths", "Close", nullptr);
                break;
            case 2:
                AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "No Ffmpeg library found", "Check Ffmpeg library path", "Close", nullptr);
                break;
            case 3:
                AlertWindow::showMessageBoxAsync(AlertWindow::WarningIcon, "No Youtube-dl library found", "Check Youtube-dl library path", "Close", nullptr);
                break;
                
            default:
                processDownload(component, progress);
                break;
        }
    }
}

void Crate::processDownload(Component::SafePointer<Crate> component, String& progress) {

    Logger::getCurrentLogger()->writeToLog("[Crate] At processDownload()");
    juce::ChildProcess ytdlChildProcess;
    String youtubeUrl = searchBarInput.getTextValue().toString();
    
    //Process download
    //==============================================================================

    String ffmpegPathForChildProcess = librariesManager.ffmpegPath;
    // If on Windows, add quotes at beginning and end of path to avoid error of ffmpeg when finding whitespaces in path
    if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0)
    {
        ffmpegPathForChildProcess = "\"" + librariesManager.ffmpegPath + "\"";
    }
    String ytdlCommand = librariesManager.youtubedlPath + " --newline -k --output " + downloadsFolder + "/%(title)s.%(ext)s --extract-audio --audio-format mp3 --ffmpeg-location " + ffmpegPathForChildProcess + " " + youtubeUrl;
    String ytdlCommandFilename = librariesManager.youtubedlPath + " --get-filename --output " + downloadsFolder + "/%(title)s.mp3 --extract-audio --audio-format mp3 --ffmpeg-location " + ffmpegPathForChildProcess + " " + youtubeUrl;

    ytdlChildProcess.start(ytdlCommand, 0x03);

    // Update progress bar while process runs.
    while (ytdlChildProcess.isRunning()) {
        char buffer[512];
        ytdlChildProcess.readProcessOutput(buffer, 512);
        std::string s (buffer);
        std::smatch m;
        std::regex e ("[0-9.]+\%");
        while (std::regex_search (s,m,e)) {
            progress = m.str();
            s = m.suffix().str();
        }
        MessageManager::getInstance()->callAsync ([component] () mutable
                                                  {
                                                      if (component != nullptr)
                                                          component->repaint();
                                                  });

    }

    Logger::getCurrentLogger()->writeToLog("[Crate] Getting filename.");
    ytdlChildProcess.start(ytdlCommandFilename, 0x03);
    Logger::getCurrentLogger()->writeToLog("[Crate] Got filename.");

    //==============================================================================

    filePath = ytdlChildProcess.readAllProcessOutput();
    Logger::getCurrentLogger()->writeToLog(filePath);
    filePath = filePath.replace("\n", "");
    filePath = filePath.replace("\r", "");

}

void Crate::downloadCompleteCallback() {
    //Log to plugin result from library
    if (filePath.startsWith("Usage") || filePath.startsWith("WARNING") || filePath.startsWith("ERROR")) {
        waveformComponent.resetThumbnail();
        statusLabel.setText("Download Error", dontSendNotification);
        debugText.setText(filePath, dontSendNotification);
        filePath = "";
    } else {
        waveformComponent.loadFile(filePath);
        waveformComponent.setCurrentAudioFile(filePath);
        statusLabel.setText("Done loading, drag waveform into your DAW", dontSendNotification);
        debugText.setText(filePath, dontSendNotification);
    }
    downloadButton.setEnabled(true);
    downloadButton.setButtonText("Download");
    isDownloading = false;
}

void Crate::setPaths()
{
    pathsWindow.setVisible(true);
}

void Crate::updateLibrariesPaths()
{
    if ((librariesManager.youtubedlPath != pathsWindow.getYotubedlPath()) || (librariesManager.ffmpegPath != pathsWindow.getFfmpegPath()))
    {
        librariesManager.updateLibrariesPaths(pathsWindow.getYotubedlPath(), pathsWindow.getFfmpegPath());
        librariesManager.updateDownloadsPath(pathsWindow.getDownloadsPath());
    }
    
    if ((librariesManager.downloadsPath != pathsWindow.getDownloadsPath()))
    {
        librariesManager.updateDownloadsPath(pathsWindow.getDownloadsPath());
    }
}

void Crate::updateYoutubedl()
{
    //Update Libraries paths if changed
    updateLibrariesPaths();
    
    juce::ChildProcess updateYtdlProcess;
    
    if ((SystemStats::getOperatingSystemType() & SystemStats::MacOSX) != 0)
    {
        String updateCommand = "sudo " +  librariesManager.youtubedlPath + " --update";
        updateYtdlProcess.start(updateCommand, 0x03);
        updateYtdlProcess.waitForProcessToFinish(30000);
        
        String consoleOut = updateYtdlProcess.readAllProcessOutput();
        consoleOut = consoleOut.replace("\n", "");
        consoleOut = consoleOut.replace("\r", "");
        
        statusLabel.setText("Update Process Finished", dontSendNotification);
        debugText.setText(consoleOut, dontSendNotification);
    }
    
    if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0)
    {
        String updateCommand = librariesManager.youtubedlPath + " --update";
        updateYtdlProcess.start(updateCommand, 0x03);
        updateYtdlProcess.waitForProcessToFinish(30000);
        
        String consoleOut = updateYtdlProcess.readAllProcessOutput();
        consoleOut = consoleOut.replace("\n", "");
        consoleOut = consoleOut.replace("\r", "");
        
        statusLabel.setText("Update Process Finished", dontSendNotification);
        debugText.setText(consoleOut, dontSendNotification);
    }
    
}

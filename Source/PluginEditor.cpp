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
    header.setButtonText("CrateDigger v0.1");
    header.setColour(TextEditor::backgroundColourId, Colours::black);
    addAndMakeVisible(header);
    
    addAndMakeVisible(debugText);

    addAndMakeVisible (searchBarInput);
    searchBarInput.setMultiLine(false);
    searchBarInput.setTextToShowWhenEmpty("Youtube URL goes here", Colours::dimgrey);
    searchBarInput.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    searchBarInput.setColour (TextEditor::shadowColourId,  Colour (0x16000000));
    
    audioFileComponent.setColour(Label::backgroundColourId, Colours::darkblue);
    addAndMakeVisible(audioFileComponent);
    addAndMakeVisible (downloadButton);
    downloadButton.onClick = [this]() { return this->downloadVideo(); };
    
    addAndMakeVisible(waveformComponent);
    setSize (400, 400);
}

CrateDigger::~CrateDigger()
{
}

void CrateDigger::setText() {
    debugText.setButtonText("Loading");
}

//==============================================================================
void CrateDigger::downloadVideo()
{
    juce::ChildProcess ytdlChildProcess;
//    titleLabel.setText (youtubeUrl, dontSendNotification);
    audioFileComponent.setText("Loading...", dontSendNotification);
    
    debugText.setButtonText("Loading...");
    this->setText();
    String youtubeUrl = searchBarInput.getTextValue().toString();
    // Determine where to save the downloaded audio
    File appDataLocation = File::getSpecialLocation( File::userApplicationDataDirectory);
    String appDataLocationString = appDataLocation.getFullPathName();
    String ytdlCommand = "/usr/local/bin/youtube-dl --output " + appDataLocationString + "/cratedigger-audio/%(title)s.%(ext)s --extract-audio --audio-format mp3 --ffmpeg-location /usr/local/bin/ffmpeg " + youtubeUrl;
    ytdlChildProcess.start(ytdlCommand,0x03);
    ytdlChildProcess.waitForProcessToFinish(30000);
    
    String ytdlCommandFilename = "/usr/local/bin/youtube-dl --get-filename --output " + appDataLocationString + "/cratedigger-audio/%(title)s.mp3 --extract-audio --audio-format mp3 --ffmpeg-location /usr/local/bin/ffmpeg " + youtubeUrl;
    ytdlChildProcess.start(ytdlCommandFilename,0x03);
    juce::String c = ytdlChildProcess.readAllProcessOutput();
    audioFileComponent.setText("Done loading, drag this into your DAW", dontSendNotification);

    downloadButton.setButtonText("Download");
    c = c.replace("\n", "");
    c = c.replace("\r", "");
    waveformComponent.loadFile(c);
    audioFileComponent.waveform.loadFile(c);
    Logger::getCurrentLogger()->writeToLog(c);
    debugText.setButtonText(c);

    audioFileComponent.setCurrentAudioFile(c);
    waveformComponent.setCurrentAudioFile(c);
}

void CrateDigger::paint (Graphics& g)
{
    
}

void CrateDigger::resized()
{
    auto area = getLocalBounds();
    auto headerHeight = 30;
    header.setBounds(area.removeFromTop(headerHeight));
    
    auto searchBarHeight = 30;
    auto searchBarArea = area.removeFromTop(searchBarHeight);
    searchBarInput.setBounds(searchBarArea.removeFromLeft(juce::jmax(80, 3 * (searchBarArea.getWidth() / 4))));
    downloadButton.setBounds(searchBarArea.removeFromLeft(juce::jmax(30, searchBarArea.getWidth() / 4)));
    
    auto debugTextHeight = 100;
    debugText.setBounds(area.removeFromTop(debugTextHeight));
    
    waveformComponent.setBoundsRelative(0.0f, 0.6f, 1.0f, 0.2f);
    
    audioFileComponent.setBoundsRelative(0.0f, 0.4f, 1.0f, 0.2f) ;
}

void AudioFileComponent::mouseDrag(const MouseEvent& e) {
    DragAndDropContainer* dragC = DragAndDropContainer::findParentDragContainerFor(this);
    if (!dragC->isDragAndDropActive()) {
        dragC->startDragging("Audio file",this);
        Logger::getCurrentLogger()->writeToLog(currentAudioFile);
        StringArray files = StringArray(currentAudioFile);
        dragC->performExternalDragDropOfFiles(files, true);
    }
}

void AudioFileComponent::setCurrentAudioFile(String filename) {
    Logger::getCurrentLogger()->writeToLog(filename);
    this->currentAudioFile = filename;
}

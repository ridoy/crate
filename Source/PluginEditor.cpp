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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
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
    waveformComponent.loadFile("");
    audioFileComponent.setText("Done loading, drag this into your DAW", dontSendNotification);

    downloadButton.setButtonText("Download");
    c = c.replace("\n", "");
    c = c.replace("\r", "");
    Logger::getCurrentLogger()->writeToLog(c);
    debugText.setButtonText(c);

    audioFileComponent.setCurrentAudioFile(c);
}

void CrateDigger::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::white);
    
    header.setButtonText("CrateDigger v0.1");
    header.setColour(TextEditor::backgroundColourId, Colours::black);
    addAndMakeVisible(header);
    
//    debugText.setMultiLine(true);
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
    
    auto audioFileComponentHeight = 50;
    audioFileComponent.setBounds(area.removeFromTop(audioFileComponentHeight));
    
    auto debugTextHeight = 100;
    debugText.setBounds(area.removeFromTop(debugTextHeight));
    
    auto waveformComponentHeight = 150;
    waveformComponent.setBounds(area.removeFromTop(waveformComponentHeight));
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

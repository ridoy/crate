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
    namePlugin.setText("CrateDigger v0.1", dontSendNotification);
    namePlugin.setColour(Label::ColourIds::textColourId, Colours::darkblue);
    namePlugin.setFont(Font(40.0f, Font::FontStyleFlags::bold));
    namePlugin.setJustificationType(Justification::centred);
    addAndMakeVisible(namePlugin);

    searchBarInput.setMultiLine(false);
    searchBarInput.setTextToShowWhenEmpty("Enter Youtube URL", Colours::whitesmoke);
    searchBarInput.setColour(TextEditor::ColourIds::backgroundColourId, Colours::lightslategrey);
    searchBarInput.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    searchBarInput.setColour (TextEditor::shadowColourId,  Colour (0x16000000));
    addAndMakeVisible (searchBarInput);
    
    downloadButton.setColour(TextButton::buttonColourId, Colours::darkblue);
    downloadButton.setAlpha(0.9f);
    addAndMakeVisible (downloadButton);
    downloadButton.onClick = [this]() { return this->downloadVideo(); };
    
    statusLabel.setText("", dontSendNotification);
    statusLabel.setFont(Font(15.0f, Font::FontStyleFlags::bold));
    statusLabel.setColour(Label::ColourIds::textColourId, Colours::dimgrey);
    statusLabel.setJustificationType(Justification::centred);
    addAndMakeVisible(statusLabel);
    
    debugText.setText("", dontSendNotification);
    debugText.setColour(Label::ColourIds::textColourId, Colours::dimgrey);
    debugText.setJustificationType(Justification::centred);
    addAndMakeVisible(debugText);
    
    addAndMakeVisible(waveformComponent);
    setSize (400, 400);
}

CrateDigger::~CrateDigger()
{
}

void CrateDigger::setText() {
    statusLabel.setText("Loading", dontSendNotification);
    debugText.setText("Loading", dontSendNotification);

}

//==============================================================================
void CrateDigger::downloadVideo()
{
    debugText.setText("Loading", dontSendNotification);
//    this->setText();
    
    juce::ChildProcess ytdlChildProcess;
    
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
    statusLabel.setText("Done loading, drag this into your DAW", dontSendNotification);

    downloadButton.setButtonText("Download");
    c = c.replace("\n", "");
    c = c.replace("\r", "");
    waveformComponent.loadFile(c);
    Logger::getCurrentLogger()->writeToLog(c);
    debugText.setText(c, dontSendNotification);

    waveformComponent.setCurrentAudioFile(c);
}

void CrateDigger::paint (Graphics& g)
{
    g.fillAll(Colours::white);
    
}

void CrateDigger::resized()
{
    namePlugin.setBoundsRelative(0.0f, 0.0f, 1.0f, 0.2f);
    
    searchBarInput.setBoundsRelative(0.1f, 0.25f, 0.8f, 0.07f);
  
    downloadButton.setBoundsRelative(0.4f, 0.35f, 0.2f, 0.1f);
    
    waveformComponent.setBoundsRelative(0.05f, 0.5f, 0.90f, 0.2f);
    
    statusLabel.setBoundsRelative(0.05f, 0.72f, 0.9f, 0.05f);
    
    debugText.setBoundsRelative(0.05f, 0.78f, 0.9f, 0.15f);
    
}


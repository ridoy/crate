/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

//==============================================================================
void NewProjectAudioProcessorEditor::downloadVideo()
{
    juce::ChildProcess a;
    // https://www.youtube.com/watch?v=Id1IRfDacy4
    String youtubeUrl = inputText.getTextValue().toString();
    titleLabel.setText (youtubeUrl, dontSendNotification);
    audioFileComponent.setText("Loading", dontSendNotification);
    
    // Determine where to save the downloaded audio
    File appDataLocation = File::getSpecialLocation( File::userApplicationDataDirectory);
    String appDataLocationString = appDataLocation.getFullPathName();
    String ytdlCommand = "/usr/local/bin/youtube-dl --output " + appDataLocationString + "/cratedigger-audio/%(title)s.%(ext)s --extract-audio --audio-format mp3 --ffmpeg-location /usr/local/bin/ffmpeg " + youtubeUrl;

    Logger::getCurrentLogger()->writeToLog(ytdlCommand);
    bool isSuccess = a.start(ytdlCommand,0x03);
    String b = a.readAllProcessOutput();
    audioFileComponent.setText("Loaded. Drag me into your DAW!", dontSendNotification);

    Logger::getCurrentLogger()->writeToLog("Enter");
    Logger::getCurrentLogger()->writeToLog(b);
    Logger::getCurrentLogger()->writeToLog("Exit");

    String ytdlCommandFilename = "/usr/local/bin/youtube-dl --get-filename --output " + appDataLocationString + "/cratedigger-audio/%(title)s.mp3 --extract-audio --audio-format mp3 --ffmpeg-location /usr/local/bin/ffmpeg " + youtubeUrl;
//    String ytdlCommandFilename = "/usr/local/bin/youtube-dl --get-filename --output /Users/ridoymajumdar/cratedigger-audio/%(title)s.mp3 --extract-audio --audio-format mp3 --ffmpeg-location /usr/local/bin/ffmpeg " + youtubeUrl;

    a.start(ytdlCommandFilename,0x03);
    juce::String c = a.readAllProcessOutput();
    c = c.replace("\n", "");
    c = c.replace("\r", "");
    downloadButton.setButtonText("Download audio from YouTube");

    Logger::getCurrentLogger()->writeToLog(c);
    audioFileComponent.setCurrentAudioFile(c);
    debugText.setText(audioFileComponent.currentAudioFile, false);

}
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::white);
    
    addAndMakeVisible (titleLabel);
    addAndMakeVisible (debugText);
    debugText.setMultiLine(true);
//    titleLabel.setFont (Font (16.0f, Font::bold));
//    titleLabel.setText ("Enter a youtube link in the box", dontSendNotification);
//    titleLabel.setColour (Label::textColourId, Colours::lightgreen);
//    titleLabel.setJustificationType (Justification::centred);

//    addAndMakeVisible (inputLabel);
//    inputLabel.attachToComponent (&inputText, true);
//    inputLabel.setColour (Label::textColourId, Colours::orange);
//    inputLabel.setJustificationType (Justification::right);
    
    addAndMakeVisible (inputText);
    inputText.setMultiLine(false);
    inputText.setTextToShowWhenEmpty("Youtube URL goes here", Colours::dimgrey);
    inputText.setColour (TextEditor::outlineColourId, Colour (0x1c000000));
    inputText.setColour (TextEditor::shadowColourId,  Colour (0x16000000));
    
    audioFileComponent.setColour(Label::backgroundColourId, Colours::darkblue);
    //audioFileComponent.setText("empty", dontSendNotification);
    addAndMakeVisible(audioFileComponent);
    addAndMakeVisible (downloadButton);
//    addAndMakeVisible (dragButton);
    downloadButton.onClick = [this]() { return this->downloadVideo(); };

}

void NewProjectAudioProcessorEditor::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
//    titleLabel   .setBounds (10,  10, getWidth() - 20,  30);
    inputText    .setBounds (10, 50, getWidth() - 110, 20);
    downloadButton    .setBounds (getWidth() - 90, 50, 80, 20);
    audioFileComponent    .setBounds (10, 150, getWidth() - 110, 20);
    debugText.setBounds(10, 250, getWidth() - 110, 50);
}

void AudioFileComponent::mouseDrag(const MouseEvent& e) {
    DragAndDropContainer* dragC = DragAndDropContainer::findParentDragContainerFor(this);
    if (!dragC->isDragAndDropActive()) {
        dragC->startDragging("description string",this);
        Logger::getCurrentLogger()->writeToLog(currentAudioFile);
        StringArray files = StringArray(currentAudioFile);

        
        dragC->performExternalDragDropOfFiles(files, true);
    }
}

void AudioFileComponent::setCurrentAudioFile(String filename) {
    this->currentAudioFile = filename;
}

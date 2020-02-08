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
    downloadButton.setButtonText("Loading");
    bool isSuccess = a.start("/usr/local/bin/youtube-dl --output \"%(title)s.%(ext)s\" --extract-audio --audio-format mp3 --ffmpeg-location /usr/local/bin/ffmpeg " + youtubeUrl,0x03);
    String b = a.readAllProcessOutput();
    
    Logger::getCurrentLogger()->writeToLog("Enter");

    Logger::getCurrentLogger()->writeToLog(b);
    Logger::getCurrentLogger()->writeToLog("Exit");
    downloadButton.setButtonText("Download audio from YouTube");
    
}
void NewProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    addAndMakeVisible (titleLabel);
    titleLabel.setFont (Font (16.0f, Font::bold));
    titleLabel.setText ("Enter a youtube link in the box", dontSendNotification);
    titleLabel.setColour (Label::textColourId, Colours::lightgreen);
    titleLabel.setJustificationType (Justification::centred);

    addAndMakeVisible (inputLabel);
    inputLabel.setText ("Youtube link:", dontSendNotification);
    inputLabel.attachToComponent (&inputText, true);
    inputLabel.setColour (Label::textColourId, Colours::orange);
    inputLabel.setJustificationType (Justification::right);
    
    addAndMakeVisible (inputText);
    inputText.setEditable (true);
    inputText.setColour (Label::backgroundColourId, Colours::darkblue);
    audioFileComponent.setColour(Label::backgroundColourId, Colours::darkblue);
    audioFileComponent.setText("blah", dontSendNotification);
    addAndMakeVisible(audioFileComponent);
    addAndMakeVisible (downloadButton);
    addAndMakeVisible (dragButton);
    downloadButton.onClick = [this]() { return this->downloadVideo(); };

}

void NewProjectAudioProcessorEditor::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    titleLabel   .setBounds (10,  10, getWidth() - 20,  30);
    inputText    .setBounds (100, 50, getWidth() - 110, 20);
    downloadButton    .setBounds (100, 100, getWidth() - 110, 20);
    audioFileComponent    .setBounds (100, 150, getWidth() - 110, 20);
}

void AudioFileComponent::mouseDrag(const MouseEvent& e) {
    DragAndDropContainer* dragC = DragAndDropContainer::findParentDragContainerFor(this);
    if (!dragC->isDragAndDropActive()) {
        dragC->startDragging("description string",this);
        StringArray files = StringArray("/Users/ridoymajumdar/Documents/JUCE/extras/AudioPluginHost/Builds/MacOSX/build/Debug/test.mp3");
        dragC->performExternalDragDropOfFiles(files, true);
    }
}

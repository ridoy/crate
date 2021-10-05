/*
  ==============================================================================

    Waveform.cpp
    Created: 10 Feb 2021 6:47:15pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#include "Waveform.h"

Waveform::Waveform() : thumbnailCache(5), thumbnail(512, formatManager, thumbnailCache) {
    thumbnail.addChangeListener(this);
    formatManager.registerBasicFormats();
    
    setSize(400, 100);
}

Waveform::~Waveform() {
    
}

void Waveform::paint(Graphics& g) {
    Rectangle<int> thumbnailBounds(getWidth(), getHeight());
    
    if(thumbnail.getNumChannels() == 0)
        paintIfNoFileLoaded(g, thumbnailBounds);
    else
        paintIfFileLoaded(g, thumbnailBounds);
}

void Waveform::resized() {
    
}

void Waveform::loadFile(String pathString) {
    if(pathString.isNotEmpty()) {
        File file(pathString);
        URL url(file);
        AudioFormatReader* reader = nullptr;
        
//        formatManager.clearFormats();
//        formatManager.registerBasicFormats();
        reader = formatManager.createReaderFor(url.getLocalFile());
        
        if(reader != nullptr) {
            thumbnail.setSource(new FileInputSource(url.getLocalFile()));
        }
    }
}

void Waveform::changeListenerCallback(ChangeBroadcaster* source) {
    if (source == &thumbnail)
        thumbnailChanged();
}

void Waveform::thumbnailChanged() {
    repaint();
}

void Waveform::paintIfNoFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds) {
    g.setColour(Colours::lightgrey);
    g.fillRect(thumbnailBounds);
    g.setColour(Colours::dimgrey);
    g.drawFittedText("Downloaded audio will appear here.", thumbnailBounds, Justification::centred, 1);
}
void Waveform::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds) {
    g.setColour(Colours::lightgrey);
    g.fillRect(thumbnailBounds);
    g.setColour(Colours::steelblue);
    thumbnail.drawChannels(g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 0.8f);
}

void Waveform::mouseDrag(const MouseEvent& e) {
    DragAndDropContainer* dragFile = DragAndDropContainer::findParentDragContainerFor(this);
    
    if (!dragFile->isDragAndDropActive()) {
        dragFile->startDragging("Audio file",this);
        StringArray files = StringArray(currentAudioFile);
        dragFile->performExternalDragDropOfFiles(files, true);
    }
}

void Waveform::setCurrentAudioFile(String filePath) {
    this->currentAudioFile = filePath;
}

void Waveform::resetThumbnail() {
    thumbnail.clear();
}



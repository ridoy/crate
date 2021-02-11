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
    File file("/Users/rodolfoortiz/Desktop/Audios\ prueba/553380__badoink__southside-funk.wav");
    FileInputStream inputStream(file);

    formatManager.clearFormats();
    formatManager.registerBasicFormats();
    formatReader = formatManager.createReaderFor(file);
    
    if(formatReader != nullptr) {
        thumbnail.setSource(new FileInputSource(file));
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
    g.setColour(Colours::darkgrey);
    g.fillRect(thumbnailBounds);
    g.setColour(Colours::white);
    g.drawFittedText("No File Downloaded", thumbnailBounds, Justification::centred, 1);
}
void Waveform::paintIfFileLoaded(Graphics& g, const Rectangle<int>& thumbnailBounds) {
    g.setColour(Colours::white);
    g.fillRect(thumbnailBounds);
    g.setColour(Colours::cadetblue);
    thumbnail.drawChannel(g, thumbnailBounds, 0.0, thumbnail.getTotalLength(), 0, 1.0f);
}

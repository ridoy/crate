/*
  ==============================================================================

    Waveform.h
    Created: 10 Feb 2021 6:47:15pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Waveform : public Component, public ChangeListener, public DragAndDropContainer {
public:
    Waveform();
    ~Waveform();
    
    void paint (Graphics&) override;
    void resized() override;
    
    void loadFile(String);
    void changeListenerCallback(ChangeBroadcaster*) override;
    void thumbnailChanged();
    
    void paintIfNoFileLoaded(Graphics&, const Rectangle<int>&);
    void paintIfFileLoaded(Graphics&, const Rectangle<int>&);
    
    void mouseDrag(const MouseEvent&) override;
    void setCurrentAudioFile(String);
    
    void resetThumbnail();
    
private:
    AudioFormatManager formatManager;
//    AudioFormatReader* formatReader {nullptr};
    AudioThumbnailCache thumbnailCache;
    AudioThumbnail thumbnail;
    
    String currentAudioFile;
    
};

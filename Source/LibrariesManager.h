/*
  ==============================================================================

    LibrariesManager.h
    Created: 20 Feb 2021 5:10:38pm
    Author:  Rodolfo Ortiz

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

struct LibrariesManager
{
    enum class Folder {
        Downloads,
        macOS_Paths,
        windows_Paths
    };

    static File createDirectory(const juce::File& file) {
        if (!file.exists())
            file.createDirectory();
        return file;
    };

    static File getApplicationDataDirectory() {
        auto file = juce::File::getSpecialLocation(juce::File::userApplicationDataDirectory)
        .getChildFile("CrateDigger-Audio");

        return createDirectory(file);
    };

    static File getFolderDirectory(Folder folder) {

        if (folder == Folder::Downloads)
            return createDirectory(getApplicationDataDirectory().getChildFile("Downloads"));

        if (folder == Folder::macOS_Paths)
            return createDirectory(getApplicationDataDirectory().getChildFile("macOS_Paths"));

        if (folder == Folder::windows_Paths)
            return createDirectory(getApplicationDataDirectory().getChildFile("windows_Paths"));
    };
    
    static void createPathFiles(String libraryName) {
        if (libraryName == "youtube-dl") {
            createDirectory(getApplicationDataDirectory().getChildFile("macOS_Paths")).getChildFile("youtube-dl_Path.txt").replaceWithText("/usr/local/bin/youtube-dl");
        }
        
        if (libraryName == "ffmpeg") {
            createDirectory(getApplicationDataDirectory().getChildFile("macOS_Paths")).getChildFile("ffmpeg_Path.txt").replaceWithText("/usr/local/bin/ffmpeg");
        }
    };
    
    void getLibrariesPaths() {
        youtubedlPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("youtube-dl_Path.txt").loadFileAsString();
        ffmpegPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("ffmpeg_Path.txt").loadFileAsString();
    };
    
    void updateLibrariesPaths(String _youtubedlPath, String _ffmpegPath) {
        getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("youtube-dl_Path.txt").replaceWithText(_youtubedlPath);
        youtubedlPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("youtube-dl_Path.txt").loadFileAsString();
        
        getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("ffmpeg_Path.txt").replaceWithText(_ffmpegPath);
        ffmpegPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("ffmpeg_Path.txt").loadFileAsString();
    };
    
    String youtubedlPath, ffmpegPath;
};

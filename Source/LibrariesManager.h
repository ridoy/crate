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
    enum class Folder
    {
        Downloads,
        macOS_Paths,
        windows_Paths
    };

    static File createDirectory(const juce::File& file)
    {
        if (!file.exists())
            file.createDirectory();
        return file;
    };

    static File getApplicationDataDirectory()
    {
        //Code if running in macOS
        if ((SystemStats::getOperatingSystemType() & SystemStats::MacOSX) != 0)
        {
            auto file = juce::File::getSpecialLocation(juce::File::globalApplicationsDirectory)
                .getChildFile("Crate-Audio");

            return createDirectory(file);
        }

        //==============================================================================
        //Code if running in Windows
        if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0)
        {
            auto file = juce::File::getSpecialLocation(juce::File::commonApplicationDataDirectory)
                .getChildFile("Crate-Audio");

            return createDirectory(file);
        }
    };

    static File getFolderDirectory(Folder folder)
    {

        if (folder == Folder::Downloads)
            return createDirectory(getApplicationDataDirectory().getChildFile("Downloads"));

        if (folder == Folder::macOS_Paths)
            return createDirectory(getApplicationDataDirectory().getChildFile("macOS_Paths"));

        if (folder == Folder::windows_Paths)
            return createDirectory(getApplicationDataDirectory().getChildFile("windows_Paths"));
    };
    
    static void createPathFiles(String locationPath)
    {
        //Code if running in macOS
        if ((SystemStats::getOperatingSystemType() & SystemStats::MacOSX) != 0) {
            if (locationPath == "youtube-dl")
            {
                createDirectory(getApplicationDataDirectory().getChildFile("macOS_Paths")).getChildFile("youtube-dl_Path.txt").replaceWithText("/Applications/Crate-Audio/youtube-dl");
            }
            
            if (locationPath == "ffmpeg")
            {
                createDirectory(getApplicationDataDirectory().getChildFile("macOS_Paths")).getChildFile("ffmpeg_Path.txt").replaceWithText("/Applications/Crate-Audio/ffmpeg");
            }
            
            if (locationPath == "downloads")
            {
                createDirectory(getApplicationDataDirectory().getChildFile("macOS_Paths")).getChildFile("downloads_Path.txt").replaceWithText("/Applications/Crate-Audio/Downloads");
            }
            
        }

        //==============================================================================
        //Code if running in Windows
        if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0)
        {
            if (locationPath == "youtube-dl")
            {
                createDirectory(getApplicationDataDirectory().getChildFile("windows_Paths")).getChildFile("youtube-dl_Path.txt").replaceWithText("C:\\ProgramData\\Crate-Audio\\youtube-dl.exe");
            }

            if (locationPath == "ffmpeg")
            {
                createDirectory(getApplicationDataDirectory().getChildFile("windows_Paths")).getChildFile("ffmpeg_Path.txt").replaceWithText("\"C:\\ProgramData\\Crate-Audio\\ffmpeg.exe\"");
            }
            
            if (locationPath == "downloads")
            {
                createDirectory(getApplicationDataDirectory().getChildFile("windows_Paths")).getChildFile("downloads_Path.txt").replaceWithText("C:\\ProgramData\\Crate-Audio\\Downloads");
            }
            
        }

    };
    
    void getLocationsPaths()
    {
        //Code if running in macOS
        if ((SystemStats::getOperatingSystemType() & SystemStats::MacOSX) != 0)
        {
            youtubedlPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("youtube-dl_Path.txt").loadFileAsString();
            ffmpegPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("ffmpeg_Path.txt").loadFileAsString();
            downloadsPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("downloads_Path.txt").loadFileAsString();
        }

        //==============================================================================
        //Code if running in Windows
        if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0)
        {
            youtubedlPath = getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("youtube-dl_Path.txt").loadFileAsString();
            ffmpegPath = getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("ffmpeg_Path.txt").loadFileAsString();
            downloadsPath = getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("downloads_Path.txt").loadFileAsString();
        }
    };
    
    void updateLibrariesPaths(String _youtubedlPath, String _ffmpegPath)
    {
        //Code if running in macOS
        if ((SystemStats::getOperatingSystemType() & SystemStats::MacOSX) != 0)
        {
            getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("youtube-dl_Path.txt").replaceWithText(_youtubedlPath);
            youtubedlPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("youtube-dl_Path.txt").loadFileAsString();
            
            getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("ffmpeg_Path.txt").replaceWithText(_ffmpegPath);
            ffmpegPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("ffmpeg_Path.txt").loadFileAsString();
        }

        //==============================================================================
        //Code if running in Windows
        if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0)
        {
            getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("youtube-dl_Path.txt").replaceWithText(_youtubedlPath);
            youtubedlPath = getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("youtube-dl_Path.txt").loadFileAsString();

            getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("ffmpeg_Path.txt").replaceWithText(_ffmpegPath);
            ffmpegPath = getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("ffmpeg_Path.txt").loadFileAsString();
        }
    };
    
    void updateDownloadsPath(String _downloads)
    {
        //Code if running in macOS
        if ((SystemStats::getOperatingSystemType() & SystemStats::MacOSX) != 0)
        {
            getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("downloads_Path.txt").replaceWithText(_downloads);
            downloadsPath = getApplicationDataDirectory().getChildFile("macOS_Paths").getChildFile("downloads_Path.txt").loadFileAsString();
        }

        //==============================================================================
        //Code if running in Windows
        if ((SystemStats::getOperatingSystemType() & SystemStats::Windows) != 0)
        {
            getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("downloads_Path.txt").replaceWithText(_downloads);
            downloadsPath = getApplicationDataDirectory().getChildFile("windows_Paths").getChildFile("downloads_Path.txt").loadFileAsString();
        }
    };
    
    String youtubedlPath, ffmpegPath, downloadsPath;
};

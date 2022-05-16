<div align="center">

# DISCONTINUED
  
Crate still works, but with lack of interest and youtube-dl being dead, I've pretty much abandonded this project.
  
If you want to use it, I highly recommend going to the installation folder and swapping youtube-dl with [yt-dlp](https://github.com/yt-dlp/yt-dlp), which is a youtube-dl fork still under active development.
  
*If you're a developer I encourage you to fork this project and maintain it. People seem to like it. I've left a checklist of work to do below*
  
![Crate VST appearance](https://www.cratevst.com/img/demo.png)

https://cratevst.com
</div>

<b>Crate</b> is a YouTube to MP3 VST Plugin for music producers.

Easily download samples from YouTube in your DAW.

Tested with FL Studio, Ableton, Logic, and Reaper. Requires macOS 10.15+ or Windows 7+

# Common Issues

**Where are my samples?**

By default, Crate downloads everything to the Crate-Audio/Downloads folder, wherever you chose that to be during installation. You can always change this in the Set Paths menu.

**""youtube-dl" can't be opened because Apple can't check it for malicious software"**

youtube-dl is the YouTube downloading library that Crate uses. Try opening Preferences > Security & Privacy and click "Open Anyway" where youtube-dl appears.

**Ableton: "The file could not be read. It may be corrupt or not licensed"**

This personally happened to me when updating from macOS 10.14 to 12. You should update your DAW to the latest version. Also, you can verify the file is not corrupted by finding it in Crate-Audio/Downloads and opening it in a media player.

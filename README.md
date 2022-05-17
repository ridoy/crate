<div align="center">

# DISCONTINUED
  
**If you're a developer I encourage you to fork this project and maintain it. People seem to like it. I've left a checklist of work to do below.**
  
Crate still works, but with lack of interest and youtube-dl being dead, I've pretty much abandonded this project.
  
If you want to use it, I highly recommend going to the Crate-Audio folder after you've installed and swapping youtube-dl with [yt-dlp](https://github.com/yt-dlp/yt-dlp), which is a youtube-dl fork still under active development.
  
(Installers are on http://cratevst.com)
  
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

# Work left to do 

If you have questions you can open an issue here and I'll still respond.

- [ ] Fix auto-updating. Google wants yt-dlp dead, so the library is constantly updated. Updates should be checked for and installed in the background. Crate users are musicians, they don't want any exposure to that stuff. 
- [ ] Clean up the design. We designed it quickly for the proof-of-concept, but it could be better.
- [ ] Save favorite samples. The typical user experience is something like Browse Youtube -> Find cool sample -> Copy paste the URL. Making it easier to come back to a sample from months ago would be cool.

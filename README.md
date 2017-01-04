This project is a plugin for the [OBS Studio] (https://obsproject.com/) broadcasting software. It adds a stopwatch source to the list of available sources in OBS Studio. Hotkeys can be assigned for enabling/disabling and resetting the stopwatch, so it can be easily toggled from within the game, currently being played.

## Build instructions
In order to compile the plugin, you will need to setup the obs-studio build environment first, including the **text_ft2_source**.

1. Go to the obs-studio/plugin folder and create an new subfolder, called **kldnk-stopwatch**.
2. Clone all suorce files from this repository into the folder.
3. Open the file **obs-studio/plugin/CMakeLists.txt** and append the following line to it: *add_subdirectory(kldnk-stopwatch)*. This will include the plugin into the obs-studio build.
4. Go to your obs-studio folder and run **cmake** to create the build scripts.
5. Run **make && make package** to create the executable.

## Final notes
* The plugin has been successfully tested on Mac and Windows
* Since verion 0.3.0 the plugin is most completely written in C++.
* I added an event mechanism for the timer events suchs as start, stop, finish. Currently only used to log these states.
* I added the functionality to bind actions to the stopwatch. The action will be fired, e.g. when the timer has finished or the stopwatch has reached its final value. A scene switcher action is prepared but without function at the moment.
* Feel free to send me feedback so I can improve the plugin.

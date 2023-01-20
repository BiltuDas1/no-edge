### noedge.exe
The noedge.exe is the main component of the whole scenario. It checks for required components and then execute with Administrator privilege.

### msedge.exe
This program redirect all parameters to default browser.

It is located under `%PROGRAMDATA%\MSEDGE\msedge.exe` and copied to `%PROGRAMFILES(X86)%\Microsoft\Edge\Application\msedge.exe`

### msedge.ini
Configuration file for [noedge.exe](#noedge.exe) and [msedge.exe](#msedge.exe). It contains many human readable configuration which is acceptable by noedge.exe and msedge.exe. It is located under `%PROGRAMDATA%\MSEDGE\msedge.ini`. If it got deleted then msedge.exe will stop working.

### search.json
The most important file which contains all the search engine and their parameters. It is used by [noedge.exe](#noedge.exe) for listening all the search engine into one window and configure [msedge.ini](#msedge.ini) according to user choice.

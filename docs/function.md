### noedge.exe
The noedge.exe is the main component of the whole scenario. It checks for required components and then execute with Administrator privilege. If you are looking for command line arguments of noedge.exe then check [parameters.md](parameters.md)

### msedge.exe
This program redirect all parameters to default browser.

It is located under `%PROGRAMDATA%\MSEDGE\msedge.exe` and copied to `%PROGRAMFILES(X86)%\Microsoft\Edge\Application\msedge.exe`

### msedge.ini
Configuration file for [noedge.exe](#noedgeexe) and [msedge.exe](#msedgeexe). It contains many human readable configuration which is acceptable by noedge.exe and msedge.exe. It is located under `%PROGRAMDATA%\MSEDGE\msedge.ini`. If it got deleted then msedge.exe will stop working. If it got deleted mistakenly then you can recreate it using [noedge.exe](#noedgeexe). For manually configuration check [msedgeini.md](msedgeini.md)

### search.json
The most important file which contains all the search engine and their parameters. It is used by [noedge.exe](#noedgeexe) for listening all the search engine into one window and configure [msedge.ini](#msedgeini) according to user choice.

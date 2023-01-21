# msedge.ini
This tutorial will tell you how to configure msedge.ini manually  
Here is a sample of msedge.ini file
```
[msedge.exe]
hash=99376139f61d90be727106a65d2640362edf6efac1a0ab8bbda6033272869cf6
name=Google
parameters=/search?q=$query$
url=www.google.com
[noedge.exe]
upgradable=true
version=1.2.0.1
```
### Supported Configurations
**Note: Bold fields are mandatory for each msedge.ini for working into latest version of noedge.exe**
#### `[msedge.exe]`
* hash - sha256 value of msedge.exe
* name - name of the Search Engine
* **parameters - search parameter of Search Engine, for example check [search.json](../search.json)**
* **url - URL of Search Engine, without protocol e.g. http, https**

#### `[noedge.exe]`
* upgradable - forces noedge.exe to fresh install, default value is false.  
* **version - version of noedge.exe which was last used for generating msedge.ini file, If you are not sure about the version then change to `0.0.0.0`. This is mandatory field, if it not present into msedge.ini file then noedge.exe will crash.**

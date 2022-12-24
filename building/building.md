# Building From Source
## Requirements
* Visual Studio 2022 Community Edition (With Workload Desktop Development with C++)
* Git bash

### Downloading Source code
* You can download the source code from release and extract it or you can use git  
```
git clone https://github.com/BiltuDas1/no-edge.git
```


## Building
1. At first create a Blank Console Project with `noedge` name in Visual Studio 2022.
[Check blank.md](./blank/blank.md)

2. Now Open the Project Folder and Move all files to the directory where all source file located (If windows prompt to overwrite files then simply press skip, don't overwrite files)

3. Open `noedge.sln` to the source code directory(It should open in Visual Studio)

4. In Solution Explorer, Right Click on `Header Files` and `Add > Existing Item...` and choose `compn.h` from Source code directory

5. Close Visual Studio and save Project

6. Now Follow Step 1 and create a Project name as `msedge`

7. And move project files to the `Source Code Directory > msedge`

8. Open `noedge.sln`, Now goto `File > Add > Existing Project` and choose `Source Code Directory > msedge > msedge.vcxproj` and Save the Project

9. Change the Solution Platform to `x86` and goto `Build > Build Solution` to Build Source Code.

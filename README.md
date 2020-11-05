# command-prompt-snake
An implementation of Snake for the Windows Command Prompt.

<p align="center">
  <img height=700 src="https://user-images.githubusercontent.com/15113769/98246409-8bf8c000-1f72-11eb-9c7b-0e1e4c9ff016.gif">
</p>

## Prerequisites

To automate building the project based on the commands contained in the Makefile the command-line tool NMAKE is used.

If you've installed Visual Studio and a C++ workload, you have all the command-line tools.

To install the command-line toolset, download the Build Tools for Visual Studio. When you run the downloaded executable, it updates and runs the Visual Studio Installer. To install only the tools you need for C++ development, select the C++ build tools workload.

## Build

Open a Developer Command Prompt window. A Developer Command Prompt window has the environment variables set for the tools, libraries, and include file paths required to build at the command line.

Change directory to the root of the project and buid it.

```shell
cd path\to\project
nmake snake
```

## Run

Run snake within the Developer Command Prompt window.

```shell
nmake run
```

Or execute the `.exe` (built following the instruction in the Build section above) within a command prompt or powershell.

```shell
cd path\to\project\build\bin
snake.exe
```
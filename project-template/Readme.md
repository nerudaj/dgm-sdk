# Readme

This project serves as a quickstart for development with dgm-lib so you can start prototyping games fast and easy. It comes with simple main menu, options for setting resolution, fullscreen and game audio, simple game loop and also a pause screen.

There are also some handy primitives already implemented such as event queue.

The environment also comes with prepared unit testing infrastructure as well as simple benchmarking sandbox.

## Dependencies

 * cmake 3.19 - Newer versions might have some issues with FetchContent
 * newest Visual Studio

All required dependencies (dgm-lib, SFML, TGUI, etc) are automatically downloaded and linked via CMake. If you want to bump any of them, update `cmake/dependencies.cmake` file. First couple of lines contains versions of those dependencies. Just bumping the version should be sufficient to update it.

## How to configure and build

Configuring is easy, if you have cmake in `%PATH%`:

```
mkdir vsbuild
cd vsbuild
cmake ..
```

Following commands will produce a `vsbuild` folder with `Example.sln` which you can open in Visual Studio and start developing. There is also a handy script `MakeRelease.bat` which performs full cleanup, configuration and build in release mode and prepares ready to ship zipfile with your game in `RELEASE` folder.

The solution file contains following important subprojects:

* Example-game - Project of the binary. Usually you don't have to edit it, just set it as Startup project. You can rename it by editing `SETTINGS_BINARY_NAME` variable in `cmake/settings.cmake`
* game-benchmark - Sandbox project for benchmarking needs. It links against game-lib so anything that is public in that lib can be benchmarked
* game-lib - All of the game logic
* lib-tests - Sandbox for writing unit tests. It links against game-lib

## How to customize

Open file `cmake/settings.cmake` where you find bunch of variables that you can customize and will affect name of the output binary, of the solution file and release package name.

## How to bump dependencies

Open file `cmake/dependencies.cmake` and simply change the version numbers at the beginning of the file of libraries that you need to update.

## How to change version numbers

Edit file `cmake/version.cmake`

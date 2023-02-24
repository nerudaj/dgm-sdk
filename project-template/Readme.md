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

You can customize your configuration by adding following flags:

 * `-DCACHE_THIRD_PARTY=ON`: This will download dependencies to the root folder under `deps` instead of your build folder. This is useful if you often reconfigure without access to the internet.
 * `-DDISABLE_TESTING=ON`: If you don't want to have unit testing projects, use this option to disable their configuration. `ctest` command will also be disabled.
 * `-DENABLE_BENCHMARKS=OFF`: Use this to automatically include Google Benchmark into your project

## How to customize

Open file `cmake/settings.cmake` where you find bunch of variables that you can customize and will affect name of the output binary, of the solution file and release package name.

## How to bump dependencies

Open file `cmake/dependencies.cmake` and simply change the version numbers at the beginning of the file of libraries that you need to update.

## How to change version numbers

Edit file `cmake/version.cmake`

## Skipping main menu

If you run the binary with parameter `-s`, it will skip the main menu and jump right into the game. If you exit the game, you'll be returned into main menu.

## Starting development

Your entry point for development is the class `AppStateIngame` and its two attributes `game` and `renderer`. The `Game` class is supposed to do all the logic during each frame - update player position, process event queue, update camera. The `Renderer` is supposed to do everything related to rendering - draw the game world and HUD (these are separated to two functions. The difference is that HUD method uses screen space coordinates while the world method renders everything in relation to world coordinates and it scrolled by changing the camera position.

When you're adding any new entity, it is recommended to add reference to it to the `EntityTable` struct which acts as a scene container. Communication between components (like firing a projectile or playing a sound) is handled via events. When adding new event, add a structure with required data to the `Events.hpp` header and then add a processing method to `EventProcessor` class. Events use a double displatch mechanism for processing.

When you want to create an event, call `EventQueue::add` to do so (it is a static method, can be called from anywhere).

## Resource files

Place your assets under the `resources` folder. It contains several subfolders for various kinds of assets. The `AppStateResourceLoader` class auto loads certain kinds of assets from these folder into `dgm::ResourceManager` that is passed down into the `AppStateIngame`.

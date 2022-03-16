# Readme

These are examples of usage of dgm-lib. They are contained within a single solution file.

## Dependencies

 * cmake 3.19 - Newer versions might have some issues with FetchContent
 * newest Visual Studio

All required dependencies (dgm-lib, SFML, etc) are automatically downloaded and linked via CMake.

## How to configure and build

Configuring is easy, if you have cmake in `%PATH%`:

```
mkdir vsbuild
cd vsbuild
cmake ..
```

Following commands will produce a `vsbuild` folder with `dgm-lib-examples.sln` which you can open in Visual Studio and start developing.

You can launch binaries directly from the Visual Studio.

## Example projects

 * example-app - Shows how to use dgm::App and dgm::AppState and layer the atop of one another
 * example-controller - Shows how to use dgm::Controller and how to bind keyboard, mouse and Xbox controller to it
 * example-particle-effects - Collection of couple particle effects using interfaces defined in dgm::ps namespace
 * example-pathfind - Shows how to use LevelD tilemap, paths and navmeshes for pathfinding
 * example-tileset - Shows how to create, load and draw a tilemap using a tileset texture and LevelD file format. It also shows how to use dgm::Collision::advanced to do collisions with a tilemap

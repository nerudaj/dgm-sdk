# Readme

These are examples of usage of dgm-lib. They are contained within a single solution file.

## Dependencies

 * cmake 3.19 - Newer versions might have some issues with FetchContent
 * newest Visual Studio

All required dependencies (dgm-lib, SFML, TGUI, etc) are automatically downloaded and linked via CMake.

## How to configure and build

Configuring is easy, if you have cmake in `%PATH%`:

```
mkdir vsbuild
cd vsbuild
cmake ..
```

Following commands will produce a `vsbuild` folder with `Example.sln` which you can open in Visual Studio and start developing.

You can launch binaries directly from the Visual Studio.

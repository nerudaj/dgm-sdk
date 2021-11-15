[![Build](https://github.com/nerudaj/dgm-sdk/actions/workflows/build.yml/badge.svg)](https://github.com/nerudaj/dgm-sdk/actions/workflows/build.yml) [![Packaging](https://github.com/nerudaj/dgm-sdk/actions/workflows/packaging.yml/badge.svg)](https://github.com/nerudaj/dgm-sdk/actions/workflows/packaging.yml)

# dgm-sdk

SDK for making games build on SFML, TGUI and dgm-lib. It builds directly atop of dgm-lib and provides examples of usage, documentation and most importantly production ready template for making your games.

# Dependencies

 * cmake 3.19 - Newer versions might have some issues with FetchContent
 * newest Visual Studio
 
All required dependencies (dgm-lib, SFML, TGUI, etc) are automatically downloaded and linked via CMake.

# Development

Subfolders `examples` and `project-template` are two individual projects and you should follow their instructions on configuration. However, to start working with them, you first need to run `bootstrap.bat`.

# Packaging

If you want to create a release candidate package, running `make-release.bat` is the easiest way to do it.

If you wish to create it manually, follow these steps:

```
bootstrap.bat
mkdir vsbuild
cd vsbuild
cmake ..
cpack
```

# Versioning

This project tries to use semantic versioning so version is formatted as MAJOR.MINOR.PATCH, where patch increments with each non-breaking change and is reset with each minor/major bump.

Minor version changes with potentially API breaking changes and major version changes only for major overhauls of the repository.

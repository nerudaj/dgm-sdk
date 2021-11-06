@echo off

set BUILDDIR=vsbuild-release

call bootstrap.bat

echo Purge previous build
rd /s /q %BUILDDIR%

echo Configuring
mkdir %BUILDDIR%
cd %BUILDDIR%
cmake ..
rem When executed from script, first call to cmake tends to fail, rerun will properly configure the project 
cmake ..

echo Building
cmake --build . --config Release

echo Packing
cpack
mkdir ..\RELEASE
copy *.zip "..\RELEASE\"

@echo off

REM For Windows

REM Set VS installation folder (edit it if the your is different)
set "VS_PATH=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\"

REM Create folder and generate VS solution by CMake
mkdir build
cd build
cmake ..

REM Remember the build directory
set "VS_BUILD_DIR=%CD%"

REM Prepare to build VS solution and return into build directory
@call "%VS_PATH%Common7\Tools\VsDevCmd.bat"
cd %VS_BUILD_DIR%

REM Build VS2017 solution
devenv /build Release graphics17a_voronoi.sln

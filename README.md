# Minigin

Minigin is a very small project using [SDL2](https://www.libsdl.org/) and [glm](https://github.com/g-truc/glm) for 2D c++ game projects. It is in no way a game engine, only a barebone start project where everything sdl related has been set up. It contains glm for vector math, to aleviate the need to write custom vector and matrix classes.

[![Build Status](https://github.com/avadae/minigin/actions/workflows/msbuild.yml/badge.svg)](https://github.com/avadae/msbuild/actions)
[![GitHub Release](https://img.shields.io/github/v/release/avadae/minigin?logo=github&sort=semver)](https://github.com/avadae/minigin/releases/latest)

# Goal

Minigin can/may be used as a start project for the exam assignment in the course [Programming 4](https://youtu.be/j96Oh6vzhmg) at DAE. In that assignment students need to recreate a popular 80's arcade game with a game engine they need to program themselves. During the course we discuss several game programming patterns, using the book '[Game Programming Patterns](https://gameprogrammingpatterns.com/)' by [Robert Nystrom](https://github.com/munificent) as reading material. 

# Disclaimer

Minigin is, despite perhaps the suggestion in its name, **not** a game engine. It is just a very simple sdl2 ready project with some of the scaffolding in place to get started. None of the patterns discussed in the course are used yet (except singleton which use we challenge during the course). It is up to the students to implement their own vision for their engine, apply patterns as they see fit, create their game as efficient as possible.

# Use

Get the source from this project, or since students need to have their work on github too, they can use this repository as a template.

## Windows version

- Install CMake 
- Install CMake and CMake Tools extensions in Visual Code
- Open the root folder in Visual Code, a "build" folder will be made by Code and the project can now be build.

## Emscripten version

- Install CMake 
- Install Emscripten
- Install Ninja
- Install python

In a terminal, navigate to the root folder. Run this: 

    mkdir build_web
    cd build_web
    emcmake cmake ..
    emmake ninja

To be able to see the webpage you can simply start a python webserver in the build_web folder

    python -m http.server

Then simply browse to http://localhost:8000 and you're good to go.

## Chocolatey

For installing all of the above I recommend using [Chocolatey](https://chocolatey.org/). You can then simply run the following to install what is needed:

    choco install -y cmake
    choco install -y emscripten
    choco install -y ninja
    choco install -y python

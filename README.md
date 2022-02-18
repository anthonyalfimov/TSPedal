# TS Pedal

![Build](https://img.shields.io/github/workflow/status/anthonyalfimov/TSPedal/Validation/main?logo=github)

My fork of Dr. Eric Tarr's repository for the Audio Developers Conference (ADC) 2021 workshop, November 19, 2021
and the University of West London (UWL) Audio Circuit Modeling Workshop, February 6-7, 2021.

Video recordings of the livestream: https://www.patreon.com/hackaudio

Python notebook following the material of the workshop (work in progress). Created by Dr. Scott Hawley
https://colab.research.google.com/drive/1SxJJc6LsKrjWAM-HhwPrLJBpUzImO5oX?usp=sharing

---

CMake configuration for the project is based on my [JUCE CMake Audio Plugin Template](https://github.com/anthonyalfimov/JUCE-CMake-Plugin-Template).

## Generating IDE project

To generate an **Xcode** project, run:
```sh
cmake -B Build -G Xcode -D CMAKE_OSX_ARCHITECTURES=arm64\;x86_64 -D CMAKE_OSX_DEPLOYMENT_TARGET=10.13
```
The `-D CMAKE_OSX_ARCHITECTURES=arm64\;x86_64` flag is required to build universal binaries.

The `-D CMAKE_OSX_DEPLOYMENT_TARGET=10.13` flag sets the minimum MacOS version to be supported.

---

To generate a **Visual Studio 2022 (17)** project, run:
```sh
cmake -B Build -G "Visual Studio 17"
```

## Building

To build the generated IDE project from the command line, run:
```sh
cmake --build Build --config Debug
```
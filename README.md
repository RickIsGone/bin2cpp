# BIN2CPP

[![Ubuntu build](https://github.com/RickIsGone/bin2cpp/actions/workflows/Ubuntu%20build.yml/badge.svg)](https://github.com/RickIsGone/bin2cpp/actions/workflows/Ubuntu%20build.yml) [![Windows build](https://github.com/RickIsGone/bin2cpp/actions/workflows/Windows%20build.yml/badge.svg)](https://github.com/RickIsGone/bin2cpp/actions/workflows/Windows%20build.yml)  

bin2cpp is a CLI tool written entirely in C++20 that embeds binary files into C++ headers.  
output files are structured like this:

```cpp
   #pragma once
   constexpr unsigned char yourFileName[fileSize]{};
```

## Prerequisites

- CMake

## Compiling

to compile run this script

```sh
   mkdir build
   cmake -S . -B build
   cmake --build build --config Release
```

## Usage

you can invoke bin2cpp by doing:

```sh
   bin2cpp yourFile
```

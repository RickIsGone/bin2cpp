# BIN2CPP

[![Ubuntu build](https://github.com/RickIsGone/bin2cpp/actions/workflows/Ubuntu%20build.yml/badge.svg)](https://github.com/RickIsGone/bin2cpp/actions/workflows/Ubuntu%20build.yml) [![Windows build](https://github.com/RickIsGone/bin2cpp/actions/workflows/Windows%20build.yml/badge.svg)](https://github.com/RickIsGone/bin2cpp/actions/workflows/Windows%20build.yml)

**bin2cpp** is a command-line tool written in C++20 that embeds binary files into C++ headers.  
The generated output files are structured as follows:

```cpp
#pragma once
constexpr unsigned char yourFileName[fileSize]{};
```

## Prerequisites

- CMake

## Installing

You can install **bin2cpp** in several ways:

- Download the latest pre-built binaries from the [latest release](https://github.com/RickIsGone/bin2cpp/releases/latest).
- If you are on an Arch-based system, you can install it from the AUR:

  ```sh
  yay -S bin2cpp-git
  ```

- To build bin2cpp from source, run:

  ```sh
  mkdir build
  cmake -S . -B build
  cmake --build build --config Release
  ```

## Usage

To use **bin2cpp**, simply run:

```sh
bin2cpp yourFile
```

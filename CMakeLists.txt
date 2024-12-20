cmake_minimum_required(VERSION 3.10.0)
project(bin2cpp VERSION 1.0.2 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(bin2cpp main.cpp funcs.cpp)


cmake_minimum_required(VERSION 3.10)
project(bin2cpp)

set(CMAKE_CXX_STANDARD 20)

add_executable(bin2cpp main.cpp funcs.cpp)

if(WIN32)
    target_link_libraries(bin2cpp ws2_32)
endif()


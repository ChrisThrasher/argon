cmake_minimum_required(VERSION 3.2)
project(argon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(argon
    src/Option.cpp
    src/Parser.cpp
    src/Position.cpp)
target_include_directories(argon PUBLIC include)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(test)
endif()

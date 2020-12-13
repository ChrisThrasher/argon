cmake_minimum_required(VERSION 3.2)
project(argon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(argon INTERFACE)
target_include_directories(argon SYSTEM INTERFACE include)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(test)
endif()

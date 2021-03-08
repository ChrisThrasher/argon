cmake_minimum_required(VERSION 3.9)
project(argon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(argon src/Option.cpp src/Parser.cpp src/Position.cpp)
add_library(argon::argon ALIAS argon)
target_include_directories(argon PUBLIC include)
target_compile_options(argon PRIVATE -Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    enable_testing()
    add_subdirectory(test)
endif()

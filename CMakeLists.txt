cmake_minimum_required(VERSION 3.11)
project(options LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    add_subdirectory(test)
endif()
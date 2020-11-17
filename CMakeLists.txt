cmake_minimum_required(VERSION 3.11)
project(options LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(options INTERFACE)
target_include_directories(options SYSTEM INTERFACE include)

option(ENABLE_TESTS "Enable tests" OFF)
if (${ENABLE_TESTS})
    enable_testing()
    add_subdirectory(test)
endif()
cmake_minimum_required(VERSION 3.11)
project(options LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(options INTERFACE)
target_include_directories(options SYSTEM INTERFACE include)

if (CMAKE_PROJECT_NAME STREQUAL ${PROJECT_NAME})
    enable_testing()
    add_subdirectory(test)
endif()
cmake_minimum_required(VERSION 3.16)
project(argon-example CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    find_package(argon 0.9.1 EXACT REQUIRED)
endif()

add_executable(example Example.cpp)
target_link_libraries(example PRIVATE argon::argon)

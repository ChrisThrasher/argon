cmake_minimum_required(VERSION 3.22)
project(argon-example CXX)

if(PROJECT_IS_TOP_LEVEL)
    find_package(argon 0.10.0 EXACT REQUIRED)
endif()

add_executable(argon-example Example.cpp)
target_link_libraries(argon-example PRIVATE argon::argon)

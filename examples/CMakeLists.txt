cmake_minimum_required(VERSION 3.22)
project(argon-example CXX)

if(PROJECT_IS_TOP_LEVEL)
    find_package(argon 0.9.1 EXACT REQUIRED)
endif()

add_executable(example Example.cpp)
target_link_libraries(example PRIVATE argon::argon)

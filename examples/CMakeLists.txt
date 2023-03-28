cmake_minimum_required(VERSION 3.22)
project(argon-example CXX)

if(PROJECT_IS_TOP_LEVEL)
    find_package(argon 0.12.0 EXACT CONFIG REQUIRED)
endif()

add_executable(argon-example Example.cpp)
target_link_libraries(argon-example PRIVATE argon::argon)

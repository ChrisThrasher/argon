cmake_minimum_required(VERSION 3.11)
project(options LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(options src/Options.cpp)
target_include_directories(options PRIVATE include)
target_compile_options(options PRIVATE
    -Werror
    -Wall
    -Wextra
)

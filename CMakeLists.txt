cmake_minimum_required(VERSION 3.16)
project(argon CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
endif()

add_library(argon src/Option.cpp src/Parser.cpp src/Position.cpp)
add_library(argon::argon ALIAS argon)
target_include_directories(argon PUBLIC include)
target_compile_features(argon PUBLIC cxx_std_11)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    return()
endif()

include(CTest)
add_subdirectory(examples)
add_subdirectory(tests)

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.cpp *.h`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} `git ls-files src/*.cpp test/Example.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

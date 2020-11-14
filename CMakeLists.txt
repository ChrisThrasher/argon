cmake_minimum_required(VERSION 3.11)
project(options LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_BUILD_TYPE Release)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG master
)
FetchContent_GetProperties(gtest)
FetchContent_Populate(gtest)
add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR} EXCLUDE_FROM_ALL)

enable_testing()
add_executable(unit_tests test/UnitTests.cpp)
target_include_directories(unit_tests PRIVATE include)
target_include_directories(unit_tests SYSTEM PRIVATE ${gtest_SOURCE_DIR}/include)
target_link_libraries(unit_tests PRIVATE gtest)
target_compile_options(unit_tests PRIVATE
    -Werror
    -Wall
    -Wextra
)
add_test(NAME unit_tests COMMAND unit_tests)
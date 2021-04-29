cmake_minimum_required(VERSION 3.14)

include(FetchContent)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_Declare(gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG master)
FetchContent_MakeAvailable(gtest)

add_executable(unit_tests UnitTests.cpp)
target_link_libraries(unit_tests PRIVATE argon gtest_main)
add_test(NAME unit_tests COMMAND unit_tests)

add_test(NAME flag--help COMMAND example --help)
set_property(TEST flag--help PROPERTY PASS_REGULAR_EXPRESSION
    "Usage
  example <filename> \\[options\\]

Argon CLI parser example program

Positions
  filename                Input file

Options
  -h, --help              Show this help text
  --version               Print program version
  -d, --debug             Debug output
  -c, --count <value>     Number of instances
  --speed <value>         Initial speed
  -o, --output <value>    Output filename")

add_test(NAME flag--version COMMAND example --version)
set_property(TEST flag--version PROPERTY PASS_REGULAR_EXPRESSION "v0.0.0")

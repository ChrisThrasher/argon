if(NOT BUILD_TESTING)
    return()
endif()

include(FetchContent)
FetchContent_Declare(Catch2
    GIT_REPOSITORY "https://github.com/catchorg/Catch2.git"
    GIT_TAG v2.13.7)
FetchContent_MakeAvailable(Catch2)

add_executable(test-argon unit_tests.cpp)
target_link_libraries(test-argon PRIVATE argon::argon Catch2::Catch2)
add_test(NAME test-argon COMMAND test-argon)

add_test(NAME test-help-flag COMMAND example --help)
set_property(TEST test-help-flag PROPERTY PASS_REGULAR_EXPRESSION
    "Usage
  example.* <filename> \\[options\\]

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

add_test(NAME test-version-flag COMMAND example --version)
set_property(TEST test-version-flag PROPERTY PASS_REGULAR_EXPRESSION "v0.0.0")

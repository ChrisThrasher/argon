if(NOT BUILD_TESTING)
    return()
endif()

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(Catch2 3.3.1 REQUIRED)
target_compile_features(Catch2 PRIVATE cxx_std_17)

add_executable(test-argon Parser.cpp)
target_link_libraries(test-argon PRIVATE argon::argon Catch2::Catch2WithMain)
catch_discover_tests(test-argon)

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
set_property(TEST test-version-flag PROPERTY PASS_REGULAR_EXPRESSION v0.0.0)

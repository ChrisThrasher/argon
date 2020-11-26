include(FetchContent)
FetchContent_Declare(
    gtest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG master
)
FetchContent_GetProperties(gtest)
FetchContent_Populate(gtest)
add_subdirectory(${gtest_SOURCE_DIR} ${gtest_BINARY_DIR} EXCLUDE_FROM_ALL)

add_executable(unit_tests UnitTests.cpp)
target_include_directories(unit_tests PRIVATE ../include)
target_link_libraries(unit_tests PRIVATE gtest)
target_compile_options(unit_tests PRIVATE
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wconversion
    -Wsign-conversion
    -Wold-style-cast
)
add_test(NAME unit_tests COMMAND unit_tests)

add_executable(example Example.cpp)
target_link_libraries(example PRIVATE options)

add_test(NAME flag-h COMMAND example -h)
set_property(TEST flag-h PROPERTY PASS_REGULAR_EXPRESSION
    ".*Options
  -h, --help      Show this help text
  --version       Print program version
  -d, --debug     Debug output
  -v, --verbose   Verbose output")

add_test(NAME flag--help COMMAND example --help)
set_property(TEST flag--help PROPERTY PASS_REGULAR_EXPRESSION
    ".*Options
  -h, --help      Show this help text
  --version       Print program version
  -d, --debug     Debug output
  -v, --verbose   Verbose output")

add_test(NAME flag--version COMMAND example --version)
set_property(TEST flag--version PROPERTY PASS_REGULAR_EXPRESSION "v0.0.0")

add_test(NAME flag--debug COMMAND example --debug)
set_property(TEST flag--debug PROPERTY PASS_REGULAR_EXPRESSION "Found debug flag")

add_test(NAME flag-vd COMMAND example -v -d)
set_property(TEST flag-vd PROPERTY PASS_REGULAR_EXPRESSION
    "Found debug flag
Found verbose flag")

add_test(NAME flag--verbose--debug COMMAND example --verbose --debug)
set_property(TEST flag--verbose--debug PROPERTY PASS_REGULAR_EXPRESSION
    "Found debug flag
Found verbose flag")

add_test(NAME flag-i COMMAND example -i /dev/ttyUSB0)
set_property(TEST flag-i PROPERTY PASS_REGULAR_EXPRESSION "Filename: /dev/ttyUSB0")

add_test(NAME flag--input COMMAND example --input /dev/ttyUSB0)
set_property(TEST flag--input PROPERTY PASS_REGULAR_EXPRESSION "Filename: /dev/ttyUSB0")

add_test(NAME flag-c COMMAND example -c 100)
set_property(TEST flag-c PROPERTY PASS_REGULAR_EXPRESSION "Count: 100")

add_test(NAME flag--count COMMAND example --count 42)
set_property(TEST flag--count PROPERTY PASS_REGULAR_EXPRESSION "Count: 42")

add_test(NAME flag--temp COMMAND example --temp 42.01)
set_property(TEST flag--temp PROPERTY PASS_REGULAR_EXPRESSION "Temp: 42.01")

add_test(NAME flag--speed COMMAND example --speed 10.1234)
set_property(TEST flag--speed PROPERTY PASS_REGULAR_EXPRESSION "Speed: 10.1234")
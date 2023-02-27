list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Catch2 3.3.2 REQUIRED)
include(Catch)

add_executable(test-argon Main.cpp Parser.cpp)
target_link_libraries(test-argon PRIVATE argon::argon Catch2::Catch2)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET test-argon PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:test-argon> $<TARGET_FILE_DIR:test-argon> COMMAND_EXPAND_LISTS)
endif()
catch_discover_tests(test-argon)

add_test(NAME --help COMMAND test-argon --help)
set_property(TEST --help PROPERTY PASS_REGULAR_EXPRESSION
    "Usage
  test-argon.* <filename> \\[options\\]

Argon CLI parser test program

Positions
  filename                Input file

Options
  -h, --help              Show this help text
  --version               Print program version
  -d, --debug             Debug output
  -c, --count <value>     Number of instances
  --speed <value>         Initial speed
  -o, --output <value>    Output filename")

add_test(NAME --version COMMAND test-argon --version)
set_property(TEST --version PROPERTY PASS_REGULAR_EXPRESSION v0.0.0)

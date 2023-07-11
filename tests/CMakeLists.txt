list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Catch2 3.3.2 REQUIRED)
include(Catch)

add_executable(test-argon Main.cpp Argument.cpp Option.cpp Parser.cpp Position.cpp)
target_link_libraries(test-argon PRIVATE argon::argon Catch2::Catch2)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET test-argon PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:test-argon> $<TARGET_FILE_DIR:test-argon> COMMAND_EXPAND_LISTS)
endif()
catch_discover_tests(test-argon)

add_test(NAME "Install argon" COMMAND
    ${CMAKE_COMMAND}
    --install ${PROJECT_BINARY_DIR}
    --prefix ${CMAKE_CURRENT_BINARY_DIR}/install/argon
    --config $<CONFIG>)
set_tests_properties("Install argon" PROPERTIES FIXTURES_SETUP install-argon)

add_test(NAME "Configure test project" COMMAND
    ${CMAKE_COMMAND}
    -S ${PROJECT_SOURCE_DIR}/examples
    -B ${CMAKE_CURRENT_BINARY_DIR}/install/build
    -G ${CMAKE_GENERATOR}
    -DCMAKE_BUILD_TYPE=$<CONFIG>
    -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
    -DCMAKE_CXX_FLAGS=${CMAKE_CXX_FLAGS}
    -Dargon_ROOT=${CMAKE_CURRENT_BINARY_DIR}/install/argon)
set_tests_properties("Configure test project" PROPERTIES FIXTURES_SETUP configure-test-project FIXTURES_REQUIRED install-argon)

add_test(NAME "Build test project" COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/install/build --config $<CONFIG>)
set_tests_properties("Build test project" PROPERTIES FIXTURES_REQUIRED configure-test-project)

add_test(NAME "Delete install" COMMAND ${CMAKE_COMMAND} -E rm -r ${CMAKE_CURRENT_BINARY_DIR}/install)
set_tests_properties("Delete install" PROPERTIES FIXTURES_CLEANUP "install-argon;configure-test-project")

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

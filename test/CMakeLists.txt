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

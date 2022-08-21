cmake_minimum_required(VERSION 3.16)
project(argon VERSION 0.8.0 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
    add_compile_options($<$<CONFIG:DEBUG>:-fsanitize=address,undefined>)
    add_link_options($<$<CONFIG:DEBUG>:-fsanitize=address,undefined>)
endif()

add_library(argon src/argument.cpp src/option.cpp src/parser.cpp src/position.cpp)
add_library(argon::argon ALIAS argon)
target_include_directories(argon PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(argon PUBLIC cxx_std_17)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(DIRECTORY include/
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        COMPONENT argon_headers)
install(TARGETS argon
        EXPORT argon-targets
        COMPONENT argon_cmake
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        COMPONENT argon_runtime
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT argon_runtime
        NAMELINK_COMPONENT argon_development
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        COMPONENT argon_development
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")
install(EXPORT argon-targets
        FILE argon-targets.cmake
        NAMESPACE argon::
        DESTINATION share/cmake/argon
        COMPONENT argon_cmake)
write_basic_package_version_file(argon-config-version.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/argon-config-version.cmake"
              "${CMAKE_CURRENT_SOURCE_DIR}/cmake/argon-config.cmake"
        DESTINATION share/cmake/argon
        COMPONENT argon_cmake)

if(NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    return()
endif()

include(CTest)
add_subdirectory(examples)
add_subdirectory(tests)

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.cpp *.h`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy
    COMMAND clang-tidy -p ${CMAKE_BINARY_DIR} `git ls-files *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

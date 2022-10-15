cmake_minimum_required(VERSION 3.16)
project(argon VERSION 0.9.1 LANGUAGES CXX DESCRIPTION "Command line argument parser")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
elseif(MSVC)
    add_compile_options(/WX /W4 /permissive- /wd4251)
endif()

include(GenerateExportHeader)

add_library(argon src/Argument.cpp src/Option.cpp src/Parser.cpp src/Position.cpp)
add_library(argon::argon ALIAS argon)
target_include_directories(argon PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_compile_features(argon PUBLIC cxx_std_17)
set_target_properties(argon PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN YES)
generate_export_header(argon EXPORT_FILE_NAME include/argon/Export.hpp)
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(argon PUBLIC ARGON_STATIC_DEFINE)
endif()

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

install(DIRECTORY include/ ${PROJECT_BINARY_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        COMPONENT argon_headers)
install(TARGETS argon
        EXPORT argon-targets
        COMPONENT argon_cmake
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        COMPONENT argon_runtime
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT argon_runtime
        NAMELINK_COMPONENT argon_development
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        COMPONENT argon_development
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT argon-targets
        FILE argon-targets.cmake
        NAMESPACE argon::
        DESTINATION share/cmake/argon
        COMPONENT argon_cmake)
write_basic_package_version_file(argon-config-version.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/argon-config-version.cmake
              ${CMAKE_CURRENT_SOURCE_DIR}/cmake/argon-config.cmake
        DESTINATION share/cmake/argon
        COMPONENT argon_cmake)

if(NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    return()
endif()

include(CTest)
add_subdirectory(docs)
add_subdirectory(examples)
add_subdirectory(tests)

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.hpp *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy
    COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR} `git ls-files *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

cmake_minimum_required(VERSION 3.24)
project(argon VERSION 0.12.0 LANGUAGES CXX DESCRIPTION "Command line argument parser" HOMEPAGE_URL https://github.com/ChrisThrasher/argon)

# Add warnings
option(ARGON_ENABLE_WARNINGS "Enable compiler warnings" OFF)
if(ARGON_ENABLE_WARNINGS)
    if(MSVC)
        add_compile_options(/W4 /permissive- /wd4251)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
        add_compile_options(-Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
    endif()
endif()

# Build library
include(GenerateExportHeader)
add_library(argon src/Argument.cpp src/Option.cpp src/Parser.cpp src/Position.cpp)
add_library(argon::argon ALIAS argon)
target_sources(argon PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include ${PROJECT_BINARY_DIR}/include
    FILES include/argon/Argument.hpp
          include/argon/Option.hpp
          include/argon/Parser.hpp
          include/argon/Position.hpp
          ${PROJECT_BINARY_DIR}/include/argon/Export.hpp)
target_compile_features(argon PUBLIC cxx_std_17)
set_target_properties(argon PROPERTIES VERSION ${PROJECT_VERSION} CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN YES)
generate_export_header(argon EXPORT_FILE_NAME include/argon/Export.hpp)

# Install library
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)
install(TARGETS argon EXPORT argon-targets
        FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT argon-targets
        NAMESPACE argon::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/argon)
write_basic_package_version_file(argon-config-version.cmake COMPATIBILITY SameMajorVersion)
install(FILES ${PROJECT_SOURCE_DIR}/cmake/argon-config.cmake
              ${PROJECT_BINARY_DIR}/argon-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_DATADIR}/argon)

# Stop configuration when consuming from a higher level project
if(NOT PROJECT_IS_TOP_LEVEL)
    return()
endif()

add_subdirectory(docs)

option(ARGON_BUILD_EXAMPLES "Build examples" OFF)
if(ARGON_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

option(ARGON_BUILD_TESTING "Build tests" OFF)
if(ARGON_BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.hpp *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR})

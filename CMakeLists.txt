cmake_minimum_required(VERSION 3.22)
project(argon VERSION 0.11.0 LANGUAGES CXX DESCRIPTION "Command line argument parser")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CMakePackageConfigHelpers)
include(GenerateExportHeader)
include(GNUInstallDirs)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
    add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion -Wold-style-cast)
elseif(MSVC)
    add_compile_options(/WX /W4 /permissive- /wd4251)
endif()

add_library(argon src/Argument.cpp src/Option.cpp src/Parser.cpp src/Position.cpp)
add_library(argon::argon ALIAS argon)
target_include_directories(argon PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>)
target_include_directories(argon SYSTEM PUBLIC $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>)
target_compile_features(argon PUBLIC cxx_std_17)
set_target_properties(argon PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(argon PROPERTIES CXX_VISIBILITY_PRESET hidden VISIBILITY_INLINES_HIDDEN YES)
generate_export_header(argon EXPORT_FILE_NAME include/argon/Export.hpp)
if(NOT BUILD_SHARED_LIBS)
    target_compile_definitions(argon PUBLIC ARGON_STATIC_DEFINE)
endif()

install(DIRECTORY include/ ${PROJECT_BINARY_DIR}/include/
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/argon-${PROJECT_VERSION}
        COMPONENT argon_headers)
install(TARGETS argon EXPORT argon-targets
        RUNTIME
            DESTINATION ${CMAKE_INSTALL_BINDIR}/argon-${PROJECT_VERSION}
            COMPONENT argon_runtime
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/argon-${PROJECT_VERSION}
            COMPONENT argon_runtime
            NAMELINK_COMPONENT argon_development
        ARCHIVE
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/argon-${PROJECT_VERSION}
            COMPONENT argon_development
        INCLUDES
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/argon-${PROJECT_VERSION})
install(EXPORT argon-targets
        FILE argon-targets.cmake
        NAMESPACE argon::
        DESTINATION ${CMAKE_INSTALL_DATADIR}/argon-${PROJECT_VERSION}
        COMPONENT argon_cmake)
write_basic_package_version_file(argon-config-version.cmake
                                 VERSION ${PROJECT_VERSION}
                                 COMPATIBILITY SameMajorVersion)
install(FILES ${PROJECT_SOURCE_DIR}/cmake/argon-config.cmake
              ${PROJECT_BINARY_DIR}/argon-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_DATADIR}/argon-${PROJECT_VERSION}
        COMPONENT argon_cmake)

include(CPack)

if(NOT PROJECT_IS_TOP_LEVEL)
    return()
endif()

add_subdirectory(docs)
add_subdirectory(examples)

include(CTest)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()

add_custom_target(format
    COMMAND clang-format -i `git ls-files *.hpp *.cpp`
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
add_custom_target(tidy COMMAND run-clang-tidy -p ${CMAKE_BINARY_DIR})
